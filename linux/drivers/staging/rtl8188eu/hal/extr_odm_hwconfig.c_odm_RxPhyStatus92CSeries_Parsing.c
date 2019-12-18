#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sw_ant_switch {int /*<<< orphan*/  antsel; } ;
struct phy_status_rpt {int cck_agc_rpt_ofdm_cfosho_a; int cck_sig_qual_ofdm_pwdb_all; int* path_rxsnr; int /*<<< orphan*/  antsel_rx_keep_2; int /*<<< orphan*/  ant_sel_b; int /*<<< orphan*/  ant_sel; int /*<<< orphan*/ * stream_rxevm; TYPE_1__* path_agc; } ;
struct odm_phy_status_info {int* RxMIMOSignalQuality; int RxPWDBAll; int BTRxRSSIPercentage; int RecvSignalPower; int SignalQuality; int* RxPwr; int* RxMIMOSignalStrength; int RxPower; int SignalStrength; void** RxSNR; } ;
struct odm_per_pkt_info {scalar_t__ Rate; scalar_t__ bPacketMatchBSSID; } ;
struct TYPE_5__ {int /*<<< orphan*/  antsel_rx_keep_2; int /*<<< orphan*/  antsel_rx_keep_1; int /*<<< orphan*/  antsel_rx_keep_0; } ;
struct TYPE_6__ {void** RxSNRdB; int /*<<< orphan*/  NumQryPhyStatusOFDM; int /*<<< orphan*/  NumQryPhyStatusCCK; } ;
struct odm_dm_struct {int bCckHighPower; int RFPathRxEnable; scalar_t__ BoardType; TYPE_2__ DM_FatTable; TYPE_3__ PhyDbgInfo; int /*<<< orphan*/  bInHctTest; struct sw_ant_switch DM_SWAT_Table; } ;
typedef  int s8 ;
typedef  void* s32 ;
struct TYPE_4__ {int gain; int trsw; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ DESC92C_RATE11M ; 
 scalar_t__ DESC92C_RATE1M ; 
 scalar_t__ DESC92C_RATEMCS15 ; 
 scalar_t__ DESC92C_RATEMCS8 ; 
 scalar_t__ ODM_BOARD_HIGHPWR ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 int RF_PATH_MAX ; 
 int odm_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 int odm_query_rxpwrpercentage (int) ; 
 scalar_t__ odm_signal_scale_mapping (struct odm_dm_struct*,int) ; 

__attribute__((used)) static void odm_RxPhyStatus92CSeries_Parsing(struct odm_dm_struct *dm_odm,
			struct odm_phy_status_info *pPhyInfo,
			u8 *pPhyStatus,
			struct odm_per_pkt_info *pPktinfo)
{
	struct sw_ant_switch *pDM_SWAT_Table = &dm_odm->DM_SWAT_Table;
	u8 i, max_spatial_stream;
	s8 rx_pwr[4], rx_pwr_all = 0;
	u8 EVM, PWDB_ALL = 0, PWDB_ALL_BT;
	u8 RSSI, total_rssi = 0;
	bool is_cck_rate;
	u8 rf_rx_num = 0;
	u8 cck_highpwr = 0;
	u8 LNA_idx, VGA_idx;

	struct phy_status_rpt *pPhyStaRpt = (struct phy_status_rpt *)pPhyStatus;

	is_cck_rate = pPktinfo->Rate >= DESC92C_RATE1M &&
		      pPktinfo->Rate <= DESC92C_RATE11M;

	pPhyInfo->RxMIMOSignalQuality[RF_PATH_A] = -1;
	pPhyInfo->RxMIMOSignalQuality[RF_PATH_B] = -1;

	if (is_cck_rate) {
		u8 cck_agc_rpt;

		dm_odm->PhyDbgInfo.NumQryPhyStatusCCK++;
		/*  (1)Hardware does not provide RSSI for CCK */
		/*  (2)PWDB, Average PWDB calculated by hardware (for rate adaptive) */

		cck_highpwr = dm_odm->bCckHighPower;

		cck_agc_rpt =  pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a;

		/* 2011.11.28 LukeLee: 88E use different LNA & VGA gain table */
		/* The RSSI formula should be modified according to the gain table */
		/* In 88E, cck_highpwr is always set to 1 */
		LNA_idx = (cck_agc_rpt & 0xE0) >> 5;
		VGA_idx = cck_agc_rpt & 0x1F;
		switch (LNA_idx) {
		case 7:
			if (VGA_idx <= 27)
				rx_pwr_all = -100 + 2 * (27-VGA_idx); /* VGA_idx = 27~2 */
			else
				rx_pwr_all = -100;
			break;
		case 6:
			rx_pwr_all = -48 + 2 * (2-VGA_idx); /* VGA_idx = 2~0 */
			break;
		case 5:
			rx_pwr_all = -42 + 2 * (7-VGA_idx); /* VGA_idx = 7~5 */
			break;
		case 4:
			rx_pwr_all = -36 + 2 * (7-VGA_idx); /* VGA_idx = 7~4 */
			break;
		case 3:
			rx_pwr_all = -24 + 2 * (7-VGA_idx); /* VGA_idx = 7~0 */
			break;
		case 2:
			if (cck_highpwr)
				rx_pwr_all = -12 + 2 * (5-VGA_idx); /* VGA_idx = 5~0 */
			else
				rx_pwr_all = -6 + 2 * (5-VGA_idx);
			break;
		case 1:
			rx_pwr_all = 8-2 * VGA_idx;
			break;
		case 0:
			rx_pwr_all = 14-2 * VGA_idx;
			break;
		default:
			break;
		}
		rx_pwr_all += 6;
		PWDB_ALL = odm_query_rxpwrpercentage(rx_pwr_all);
		if (!cck_highpwr) {
			if (PWDB_ALL >= 80)
				PWDB_ALL = ((PWDB_ALL-80)<<1) + ((PWDB_ALL-80)>>1) + 80;
			else if ((PWDB_ALL <= 78) && (PWDB_ALL >= 20))
				PWDB_ALL += 3;
			if (PWDB_ALL > 100)
				PWDB_ALL = 100;
		}

		pPhyInfo->RxPWDBAll = PWDB_ALL;
		pPhyInfo->BTRxRSSIPercentage = PWDB_ALL;
		pPhyInfo->RecvSignalPower = rx_pwr_all;
		/*  (3) Get Signal Quality (EVM) */
		if (pPktinfo->bPacketMatchBSSID) {
			u8 SQ, SQ_rpt;

			if (pPhyInfo->RxPWDBAll > 40 && !dm_odm->bInHctTest) {
				SQ = 100;
			} else {
				SQ_rpt = pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all;

				if (SQ_rpt > 64)
					SQ = 0;
				else if (SQ_rpt < 20)
					SQ = 100;
				else
					SQ = ((64-SQ_rpt) * 100) / 44;
			}
			pPhyInfo->SignalQuality = SQ;
			pPhyInfo->RxMIMOSignalQuality[RF_PATH_A] = SQ;
			pPhyInfo->RxMIMOSignalQuality[RF_PATH_B] = -1;
		}
	} else { /* is OFDM rate */
		dm_odm->PhyDbgInfo.NumQryPhyStatusOFDM++;

		/*  (1)Get RSSI for HT rate */

		for (i = RF_PATH_A; i < RF_PATH_MAX; i++) {
			/*  2008/01/30 MH we will judge RF RX path now. */
			if (dm_odm->RFPathRxEnable & BIT(i))
				rf_rx_num++;

			rx_pwr[i] = ((pPhyStaRpt->path_agc[i].gain & 0x3F) * 2) - 110;

			pPhyInfo->RxPwr[i] = rx_pwr[i];

			/* Translate DBM to percentage. */
			RSSI = odm_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += RSSI;

			/* Modification for ext-LNA board */
			if (dm_odm->BoardType == ODM_BOARD_HIGHPWR) {
				if ((pPhyStaRpt->path_agc[i].trsw) == 1)
					RSSI = (RSSI > 94) ? 100 : (RSSI + 6);
				else
					RSSI = (RSSI <= 16) ? (RSSI >> 3) : (RSSI - 16);

				if ((RSSI <= 34) && (RSSI >= 4))
					RSSI -= 4;
			}

			pPhyInfo->RxMIMOSignalStrength[i] = (u8)RSSI;

			/* Get Rx snr value in DB */
			pPhyInfo->RxSNR[i] = (s32)(pPhyStaRpt->path_rxsnr[i]/2);
			dm_odm->PhyDbgInfo.RxSNRdB[i] = (s32)(pPhyStaRpt->path_rxsnr[i]/2);
		}
		/*  (2)PWDB, Average PWDB calculated by hardware (for rate adaptive) */
		rx_pwr_all = (((pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all) >> 1) & 0x7f) - 110;

		PWDB_ALL = odm_query_rxpwrpercentage(rx_pwr_all);
		PWDB_ALL_BT = PWDB_ALL;

		pPhyInfo->RxPWDBAll = PWDB_ALL;
		pPhyInfo->BTRxRSSIPercentage = PWDB_ALL_BT;
		pPhyInfo->RxPower = rx_pwr_all;
		pPhyInfo->RecvSignalPower = rx_pwr_all;

		/*  (3)EVM of HT rate */
		if (pPktinfo->Rate >= DESC92C_RATEMCS8 && pPktinfo->Rate <= DESC92C_RATEMCS15)
			max_spatial_stream = 2; /* both spatial stream make sense */
		else
			max_spatial_stream = 1; /* only spatial stream 1 makes sense */

		for (i = 0; i < max_spatial_stream; i++) {
			/*  Do not use shift operation like "rx_evmX >>= 1" because the compilor of free build environment */
			/*  fill most significant bit to "zero" when doing shifting operation which may change a negative */
			/*  value to positive one, then the dbm value (which is supposed to be negative)  is not correct anymore. */
			EVM = odm_evm_db_to_percentage((pPhyStaRpt->stream_rxevm[i]));	/* dbm */

			if (pPktinfo->bPacketMatchBSSID) {
				if (i == RF_PATH_A) /*  Fill value in RFD, Get the first spatial stream only */
					pPhyInfo->SignalQuality = (u8)(EVM & 0xff);
				pPhyInfo->RxMIMOSignalQuality[i] = (u8)(EVM & 0xff);
			}
		}
	}
	/* UI BSS List signal strength(in percentage), make it good looking, from 0~100. */
	/* It is assigned to the BSS List in GetValueFromBeaconOrProbeRsp(). */
	if (is_cck_rate) {
		pPhyInfo->SignalStrength = (u8)(odm_signal_scale_mapping(dm_odm, PWDB_ALL));/* PWDB_ALL; */
	} else {
		if (rf_rx_num != 0)
			pPhyInfo->SignalStrength = (u8)(odm_signal_scale_mapping(dm_odm, total_rssi /= rf_rx_num));
	}

	/* For 92C/92D HW (Hybrid) Antenna Diversity */
	pDM_SWAT_Table->antsel = pPhyStaRpt->ant_sel;
	/* For 88E HW Antenna Diversity */
	dm_odm->DM_FatTable.antsel_rx_keep_0 = pPhyStaRpt->ant_sel;
	dm_odm->DM_FatTable.antsel_rx_keep_1 = pPhyStaRpt->ant_sel_b;
	dm_odm->DM_FatTable.antsel_rx_keep_2 = pPhyStaRpt->antsel_rx_keep_2;
}