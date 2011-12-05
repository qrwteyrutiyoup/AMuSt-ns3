/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Manuel Requena <manuel.requena@cttc.es>
 */

#ifndef LTE_TEST_ENTITIES_H
#define LTE_TEST_ENTITIES_H

#include "ns3/test.h"
// #include "ns3/type-id.h"

#include "ns3/lte-mac-sap.h"
#include "ns3/lte-rlc-sap.h"
#include "ns3/lte-pdcp-sap.h"


using namespace ns3;


/**
 * This class implements a testing RRC entity
 */
class LteTestRrc : public Object
{
    friend class LtePdcpSpecificLtePdcpSapUser<LteTestRrc>;
//   friend class EnbMacMemberLteEnbCmacSapProvider;
//   friend class EnbMacMemberLteMacSapProvider<LteTestMac>;
//   friend class EnbMacMemberFfMacSchedSapUser;
//   friend class EnbMacMemberFfMacCschedSapUser;
//   friend class EnbMacMemberLteEnbPhySapUser;

  public:
    static TypeId GetTypeId (void);

    LteTestRrc (void);
    virtual ~LteTestRrc (void);
    virtual void DoDispose (void);


    /**
    * \brief Set the PDCP SAP provider
    * \param s a pointer to the PDCP SAP provider
    */
    void SetLtePdcpSapProvider (LtePdcpSapProvider* s);
    /**
    * \brief Get the PDCP SAP user
    * \return a pointer to the SAP user of the RLC
    */
    LtePdcpSapUser* GetLtePdcpSapUser (void);

    void Start ();

    void SendData (Time at, std::string dataToSend);
    std::string GetDataReceived (void);

  private:
    // Interface forwarded by LtePdcpSapUser
    virtual void DoReceiveRrcPdu (Ptr<Packet> p);

    LtePdcpSapUser* m_pdcpSapUser;
    LtePdcpSapProvider* m_pdcpSapProvider;

    std::string m_receivedData;

};

/////////////////////////////////////////////////////////////////////

/**
 * This class implements a testing PDCP entity
 */
class LteTestPdcp : public Object
{
    friend class LteRlcSpecificLteRlcSapUser<LteTestPdcp>;
//   friend class EnbMacMemberLteEnbCmacSapProvider;
//   friend class EnbMacMemberLteMacSapProvider<LteTestMac>;
//   friend class EnbMacMemberFfMacSchedSapUser;
//   friend class EnbMacMemberFfMacCschedSapUser;
//   friend class EnbMacMemberLteEnbPhySapUser;

  public:
    static TypeId GetTypeId (void);

    LteTestPdcp (void);
    virtual ~LteTestPdcp (void);
    virtual void DoDispose (void);


    /**
    * \brief Set the RLC SAP provider
    * \param s a pointer to the RLC SAP provider
    */
    void SetLteRlcSapProvider (LteRlcSapProvider* s);
    /**
    * \brief Get the RLC SAP user
    * \return a pointer to the SAP user of the RLC
    */
    LteRlcSapUser* GetLteRlcSapUser (void);

    void Start ();

    void SendData (Time time, std::string dataToSend);
    std::string GetDataReceived (void);

  private:
    // Interface forwarded by LteRlcSapUser
    virtual void DoReceivePdcpPdu (Ptr<Packet> p);

    LteRlcSapUser* m_rlcSapUser;
    LteRlcSapProvider* m_rlcSapProvider;

    std::string m_receivedData;

};

/////////////////////////////////////////////////////////////////////

/**
 * This class implements a testing loopback MAC layer
 */
class LteTestMac : public Object
{
//   friend class EnbMacMemberLteEnbCmacSapProvider;
    friend class EnbMacMemberLteMacSapProvider<LteTestMac>;
//   friend class EnbMacMemberFfMacSchedSapUser;
//   friend class EnbMacMemberFfMacCschedSapUser;
//   friend class EnbMacMemberLteEnbPhySapUser;

  public:
    static TypeId GetTypeId (void);

    LteTestMac (void);
    virtual ~LteTestMac (void);
    virtual void DoDispose (void);

    void SendTxOpportunity (Time, uint32_t);
    std::string GetDataReceived (void);

    /**
     * \brief Set the MAC SAP user
     * \param s a pointer to the MAC SAP user
     */
    void SetLteMacSapUser (LteMacSapUser* s);
    /**
     * \brief Get the MAC SAP provider
     * \return a pointer to the SAP provider of the MAC
     */
    LteMacSapProvider* GetLteMacSapProvider (void);

    /**
     * \brief Set the other side of the MAC Loopback
     * \param s a pointer to the other side of the MAC loopback
     */
    void SetLteMacLoopback (Ptr<LteTestMac> s);

    /**
     *
     */
    void SetPdcpHeaderPresent (bool present);

    /**
     *
     */
    void SetRlcAmHeaderPresent (bool present);

    /**
     *
     */
    void SetTxOpportunityMode (uint8_t mode);

    typedef enum {
      MANUAL_MODE     = 0,
      AUTOMATIC_MODE  = 1
    } TxOpportunityMode_t;

  private:
    // forwarded from LteMacSapProvider
    void DoTransmitPdu (LteMacSapProvider::TransmitPduParameters);
    void DoReportBufferStatus (LteMacSapProvider::ReportBufferStatusParameters);

    LteMacSapProvider* m_macSapProvider;
    LteMacSapUser* m_macSapUser;
    Ptr<LteTestMac> m_macLoopback;

    std::string m_receivedData;

    bool m_pdcpHeaderPresent;
    bool m_rlcAmHeaderPresent;
    bool m_txOpportunityMode;

};

#endif /* LTE_TEST_MAC_H */