#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct odm_phy_info {int* rx_mimo_signal_quality; int rx_pwd_ba11; int bt_rx_rssi_percentage; int signal_quality; int* rx_mimo_signal_strength; int SignalStrength; int signal_strength; void* recv_signal_power; void* rx_power; scalar_t__* rx_snr; void** rx_pwr; } ;
struct odm_packet_info {scalar_t__ data_rate; } ;
typedef  void* s8 ;
typedef  scalar_t__ s32 ;
struct TYPE_9__ {scalar_t__* RxSNRdB; int /*<<< orphan*/  NumQryPhyStatusOFDM; int /*<<< orphan*/  NumQryPhyStatusCCK; } ;
struct TYPE_11__ {int RFPathRxEnable; TYPE_2__ PhyDbgInfo; int /*<<< orphan*/  bInHctTest; } ;
struct TYPE_10__ {int cck_agc_rpt_ofdm_cfosho_a; int cck_sig_qual_ofdm_pwdb_all; int* path_rxsnr; int /*<<< orphan*/  path_cfotail; int /*<<< orphan*/ * stream_rxevm; TYPE_1__* path_agc; } ;
struct TYPE_8__ {int gain; } ;
typedef  TYPE_3__* PPHY_STATUS_RPT_8192CD_T ;
typedef  TYPE_4__* PDM_ODM_T ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ DESC_RATE11M ; 
 scalar_t__ DESC_RATEMCS15 ; 
 scalar_t__ DESC_RATEMCS8 ; 
 int /*<<< orphan*/  ODM_ParsingCFO (TYPE_4__*,struct odm_packet_info*,int /*<<< orphan*/ ) ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 int ODM_RF_PATH_MAX ; 
 void* odm_CCKRSSI_8723B (int,int) ; 
 int odm_EVMdbToPercentage (int /*<<< orphan*/ ) ; 
 int odm_QueryRxPwrPercentage (void*) ; 
 scalar_t__ odm_SignalScaleMapping (TYPE_4__*,int) ; 

__attribute__((used)) static void odm_RxPhyStatus92CSeries_Parsing(
	PDM_ODM_T pDM_Odm,
	struct odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	struct odm_packet_info *pPktinfo
)
{
	u8 i, Max_spatial_stream;
	s8 rx_pwr[4], rx_pwr_all = 0;
	u8 EVM, PWDB_ALL = 0, PWDB_ALL_BT;
	u8 RSSI, total_rssi = 0;
	bool isCCKrate = false;
	u8 rf_rx_num = 0;
	u8 LNA_idx, VGA_idx;
	PPHY_STATUS_RPT_8192CD_T pPhyStaRpt = (PPHY_STATUS_RPT_8192CD_T)pPhyStatus;

	isCCKrate = pPktinfo->data_rate <= DESC_RATE11M;
	pPhyInfo->rx_mimo_signal_quality[ODM_RF_PATH_A] = -1;
	pPhyInfo->rx_mimo_signal_quality[ODM_RF_PATH_B] = -1;


	if (isCCKrate) {
		u8 cck_agc_rpt;

		pDM_Odm->PhyDbgInfo.NumQryPhyStatusCCK++;
		/*  */
		/*  (1)Hardware does not provide RSSI for CCK */
		/*  (2)PWDB, Average PWDB cacluated by hardware (for rate adaptive) */
		/*  */

		cck_agc_rpt =  pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a ;

		/* 2011.11.28 LukeLee: 88E use different LNA & VGA gain table */
		/* The RSSI formula should be modified according to the gain table */
		LNA_idx = ((cck_agc_rpt & 0xE0)>>5);
		VGA_idx = (cck_agc_rpt & 0x1F);
		rx_pwr_all = odm_CCKRSSI_8723B(LNA_idx, VGA_idx);
		PWDB_ALL = odm_QueryRxPwrPercentage(rx_pwr_all);
		if (PWDB_ALL > 100)
			PWDB_ALL = 100;

		pPhyInfo->rx_pwd_ba11 = PWDB_ALL;
		pPhyInfo->bt_rx_rssi_percentage = PWDB_ALL;
		pPhyInfo->recv_signal_power = rx_pwr_all;
		/*  */
		/*  (3) Get Signal Quality (EVM) */
		/*  */
		/* if (pPktinfo->bPacketMatchBSSID) */
		{
			u8 SQ, SQ_rpt;

			if (pPhyInfo->rx_pwd_ba11 > 40 && !pDM_Odm->bInHctTest)
				SQ = 100;
			else {
				SQ_rpt = pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all;

				if (SQ_rpt > 64)
					SQ = 0;
				else if (SQ_rpt < 20)
					SQ = 100;
				else
					SQ = ((64-SQ_rpt) * 100) / 44;

			}

			/* DbgPrint("cck SQ = %d\n", SQ); */
			pPhyInfo->signal_quality = SQ;
			pPhyInfo->rx_mimo_signal_quality[ODM_RF_PATH_A] = SQ;
			pPhyInfo->rx_mimo_signal_quality[ODM_RF_PATH_B] = -1;
		}
	} else { /* is OFDM rate */
		pDM_Odm->PhyDbgInfo.NumQryPhyStatusOFDM++;

		/*  */
		/*  (1)Get RSSI for HT rate */
		/*  */

		for (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX; i++) {
			/*  2008/01/30 MH we will judge RF RX path now. */
			if (pDM_Odm->RFPathRxEnable & BIT(i))
				rf_rx_num++;
			/* else */
				/* continue; */

			rx_pwr[i] = ((pPhyStaRpt->path_agc[i].gain&0x3F)*2) - 110;


			pPhyInfo->rx_pwr[i] = rx_pwr[i];

			/* Translate DBM to percentage. */
			RSSI = odm_QueryRxPwrPercentage(rx_pwr[i]);
			total_rssi += RSSI;
			/* RT_DISP(FRX, RX_PHY_SS, ("RF-%d RXPWR =%x RSSI =%d\n", i, rx_pwr[i], RSSI)); */

			pPhyInfo->rx_mimo_signal_strength[i] = (u8) RSSI;

			/* Get Rx snr value in DB */
			pPhyInfo->rx_snr[i] = pDM_Odm->PhyDbgInfo.RxSNRdB[i] = (s32)(pPhyStaRpt->path_rxsnr[i]/2);
		}


		/*  */
		/*  (2)PWDB, Average PWDB cacluated by hardware (for rate adaptive) */
		/*  */
		rx_pwr_all = (((pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all) >> 1)&0x7f)-110;

		PWDB_ALL_BT = PWDB_ALL = odm_QueryRxPwrPercentage(rx_pwr_all);
		/* RT_DISP(FRX, RX_PHY_SS, ("PWDB_ALL =%d\n", PWDB_ALL)); */

		pPhyInfo->rx_pwd_ba11 = PWDB_ALL;
		/* ODM_RT_TRACE(pDM_Odm, ODM_COMP_RSSI_MONITOR, ODM_DBG_LOUD, ("ODM OFDM RSSI =%d\n", pPhyInfo->rx_pwd_ba11)); */
		pPhyInfo->bt_rx_rssi_percentage = PWDB_ALL_BT;
		pPhyInfo->rx_power = rx_pwr_all;
		pPhyInfo->recv_signal_power = rx_pwr_all;

		{/* pMgntInfo->CustomerID != RT_CID_819x_Lenovo */
			/*  */
			/*  (3)EVM of HT rate */
			/*  */
			if (pPktinfo->data_rate >= DESC_RATEMCS8 && pPktinfo->data_rate <= DESC_RATEMCS15)
				Max_spatial_stream = 2; /* both spatial stream make sense */
			else
				Max_spatial_stream = 1; /* only spatial stream 1 makes sense */

			for (i = 0; i < Max_spatial_stream; i++) {
				/*  Do not use shift operation like "rx_evmX >>= 1" because the compilor of free build environment */
				/*  fill most significant bit to "zero" when doing shifting operation which may change a negative */
				/*  value to positive one, then the dbm value (which is supposed to be negative)  is not correct anymore. */
				EVM = odm_EVMdbToPercentage((pPhyStaRpt->stream_rxevm[i]));	/* dbm */

				/* RT_DISP(FRX, RX_PHY_SQ, ("RXRATE =%x RXEVM =%x EVM =%s%d\n", */
				/* GET_RX_STATUS_DESC_RX_MCS(pDesc), pDrvInfo->rxevm[i], "%", EVM)); */

				/* if (pPktinfo->bPacketMatchBSSID) */
				{
					if (i == ODM_RF_PATH_A) /*  Fill value in RFD, Get the first spatial stream only */
						pPhyInfo->signal_quality = (u8)(EVM & 0xff);

					pPhyInfo->rx_mimo_signal_quality[i] = (u8)(EVM & 0xff);
				}
			}
		}

		ODM_ParsingCFO(pDM_Odm, pPktinfo, pPhyStaRpt->path_cfotail);

	}

	/* UI BSS List signal strength(in percentage), make it good looking, from 0~100. */
	/* It is assigned to the BSS List in GetValueFromBeaconOrProbeRsp(). */
	if (isCCKrate) {
#ifdef CONFIG_SKIP_SIGNAL_SCALE_MAPPING
		pPhyInfo->SignalStrength = (u8)PWDB_ALL;
#else
		pPhyInfo->signal_strength = (u8)(odm_SignalScaleMapping(pDM_Odm, PWDB_ALL));/* PWDB_ALL; */
#endif
	} else {
		if (rf_rx_num != 0) {
#ifdef CONFIG_SKIP_SIGNAL_SCALE_MAPPING
			total_rssi /= rf_rx_num;
			pPhyInfo->signal_strength = (u8)total_rssi;
#else
			pPhyInfo->signal_strength = (u8)(odm_SignalScaleMapping(pDM_Odm, total_rssi /= rf_rx_num));
#endif
		}
	}

	/* DbgPrint("isCCKrate = %d, pPhyInfo->rx_pwd_ba11 = %d, pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a = 0x%x\n", */
		/* isCCKrate, pPhyInfo->rx_pwd_ba11, pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a); */
}