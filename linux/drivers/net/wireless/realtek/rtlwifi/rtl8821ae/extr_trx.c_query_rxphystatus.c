#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rx_fwinfo_8821ae {int pwdb_all; } ;
struct rtl_stats {int is_cck; int packet_matchbssid; int packet_toself; int packet_beacon; int* rx_mimo_signalquality; int rx_pwdb_all; int recvsignalpower; int signalquality; int* rx_snr; int* rx_mimo_signalstrength; int rxpower; scalar_t__ rate; int* rx_mimo_evm_dbm; int signalstrength; scalar_t__ is_vht; scalar_t__ is_ht; void** cfo_tail; void** cfo_short; } ;
struct TYPE_6__ {int* cfo_tail; int /*<<< orphan*/  packet_count; scalar_t__* rfpath_rxenable; } ;
struct TYPE_5__ {int* rx_snr_db; } ;
struct TYPE_8__ {scalar_t__ hw_type; } ;
struct rtl_phy {scalar_t__ cck_high_power; } ;
struct rtl_priv {TYPE_2__ dm; TYPE_1__ stats; TYPE_4__ rtlhal; struct rtl_phy phy; } ;
struct TYPE_7__ {int /*<<< orphan*/  antsel_rx_keep_1; int /*<<< orphan*/  antsel_rx_keep_0; } ;
struct rtl_dm {TYPE_3__ fat_table; } ;
struct phy_status_rpt {int* cfosho; int pwdb_all; int* gain_trsw; int* rxsnr; int* cfotail; int /*<<< orphan*/  antidx_antb; int /*<<< orphan*/  antidx_anta; int /*<<< orphan*/ * rxevm; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ DESC_RATEMCS15 ; 
 scalar_t__ DESC_RATEMCS8 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS9 ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int RF6052_MAX_PATH ; 
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int _rtl8821ae_evm_dbm_jaguar (int /*<<< orphan*/ ) ; 
 void* odm_cfo (int) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 int rtl_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_query_rxpwrpercentage (int) ; 
 scalar_t__ rtl_signal_scale_mapping (struct ieee80211_hw*,int) ; 

__attribute__((used)) static void query_rxphystatus(struct ieee80211_hw *hw,
			      struct rtl_stats *pstatus, __le32 *pdesc,
			      struct rx_fwinfo_8821ae *p_drvinfo,
			      bool bpacket_match_bssid,
			      bool bpacket_toself, bool packet_beacon)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct phy_status_rpt *p_phystrpt = (struct phy_status_rpt *)p_drvinfo;
	struct rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, evmdbm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck = pstatus->is_cck;
	u8 lan_idx, vga_idx;

	/* Record it for next packet processing */
	pstatus->packet_matchbssid = bpacket_match_bssid;
	pstatus->packet_toself = bpacket_toself;
	pstatus->packet_beacon = packet_beacon;
	pstatus->rx_mimo_signalquality[0] = -1;
	pstatus->rx_mimo_signalquality[1] = -1;

	if (is_cck) {
		u8 cck_highpwr;
		u8 cck_agc_rpt;

		cck_agc_rpt = p_phystrpt->cfosho[0];

		/* (1)Hardware does not provide RSSI for CCK
		 * (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		cck_highpwr = (u8)rtlphy->cck_high_power;

		lan_idx = ((cck_agc_rpt & 0xE0) >> 5);
		vga_idx = (cck_agc_rpt & 0x1f);
		if (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8812AE) {
			switch (lan_idx) {
			case 7:
				if (vga_idx <= 27)
					/*VGA_idx = 27~2*/
					rx_pwr_all = -100 + 2*(27-vga_idx);
				else
					rx_pwr_all = -100;
				break;
			case 6:
				/*VGA_idx = 2~0*/
				rx_pwr_all = -48 + 2*(2-vga_idx);
				break;
			case 5:
				/*VGA_idx = 7~5*/
				rx_pwr_all = -42 + 2*(7-vga_idx);
				break;
			case 4:
				/*VGA_idx = 7~4*/
				rx_pwr_all = -36 + 2*(7-vga_idx);
				break;
			case 3:
				/*VGA_idx = 7~0*/
				rx_pwr_all = -24 + 2*(7-vga_idx);
				break;
			case 2:
				if (cck_highpwr)
					/*VGA_idx = 5~0*/
					rx_pwr_all = -12 + 2*(5-vga_idx);
				else
					rx_pwr_all = -6 + 2*(5-vga_idx);
				break;
			case 1:
				rx_pwr_all = 8-2*vga_idx;
				break;
			case 0:
				rx_pwr_all = 14-2*vga_idx;
				break;
			default:
				break;
			}
			rx_pwr_all += 6;
			pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
			if (!cck_highpwr) {
				if (pwdb_all >= 80)
					pwdb_all =
					  ((pwdb_all - 80)<<1) +
					 ((pwdb_all - 80)>>1) + 80;
				else if ((pwdb_all <= 78) && (pwdb_all >= 20))
					pwdb_all += 3;
				if (pwdb_all > 100)
					pwdb_all = 100;
			}
		} else { /* 8821 */
			s8 pout = -6;

			switch (lan_idx) {
			case 5:
				rx_pwr_all = pout - 32 - (2*vga_idx);
					break;
			case 4:
				rx_pwr_all = pout - 24 - (2*vga_idx);
					break;
			case 2:
				rx_pwr_all = pout - 11 - (2*vga_idx);
					break;
			case 1:
				rx_pwr_all = pout + 5 - (2*vga_idx);
					break;
			case 0:
				rx_pwr_all = pout + 21 - (2*vga_idx);
					break;
			}
			pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		}

		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3) Get Signal Quality (EVM) */
		if (bpacket_match_bssid) {
			u8 sq;

			if (pstatus->rx_pwdb_all > 40) {
				sq = 100;
			} else {
				sq = p_phystrpt->pwdb_all;
				if (sq > 64)
					sq = 0;
				else if (sq < 20)
					sq = 100;
				else
					sq = ((64 - sq) * 100) / 44;
			}

			pstatus->signalquality = sq;
			pstatus->rx_mimo_signalquality[0] = sq;
			pstatus->rx_mimo_signalquality[1] = -1;
		}
	} else {
		/* (1)Get RSSI for HT rate */
		for (i = RF90_PATH_A; i < RF6052_MAX_PATH; i++) {
			/* we will judge RF RX path now. */
			if (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = (p_phystrpt->gain_trsw[i] & 0x7f) - 110;

			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;

			/* Get Rx snr value in DB */
			pstatus->rx_snr[i] = p_phystrpt->rxsnr[i] / 2;
			rtlpriv->stats.rx_snr_db[i] = p_phystrpt->rxsnr[i] / 2;

			pstatus->cfo_short[i] = odm_cfo(p_phystrpt->cfosho[i]);
			pstatus->cfo_tail[i] = odm_cfo(p_phystrpt->cfotail[i]);
			/* Record Signal Strength for next packet */
			pstatus->rx_mimo_signalstrength[i] = (u8)rssi;
		}

		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->rxpower = rx_pwr_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3)EVM of HT rate */
		if ((pstatus->is_ht && pstatus->rate >= DESC_RATEMCS8 &&
		     pstatus->rate <= DESC_RATEMCS15) ||
		    (pstatus->is_vht &&
		     pstatus->rate >= DESC_RATEVHT2SS_MCS0 &&
		     pstatus->rate <= DESC_RATEVHT2SS_MCS9))
			max_spatial_stream = 2;
		else
			max_spatial_stream = 1;

		for (i = 0; i < max_spatial_stream; i++) {
			evm = rtl_evm_db_to_percentage(p_phystrpt->rxevm[i]);
			evmdbm = _rtl8821ae_evm_dbm_jaguar(p_phystrpt->rxevm[i]);

			if (bpacket_match_bssid) {
				/* Fill value in RFD, Get the first
				 * spatial stream only
				 */
				if (i == 0)
					pstatus->signalquality = evm;
				pstatus->rx_mimo_signalquality[i] = evm;
				pstatus->rx_mimo_evm_dbm[i] = evmdbm;
			}
		}
		if (bpacket_match_bssid) {
			for (i = RF90_PATH_A; i <= RF90_PATH_B; i++)
				rtl_priv(hw)->dm.cfo_tail[i] =
					(s8)p_phystrpt->cfotail[i];

			rtl_priv(hw)->dm.packet_count++;
		}
	}

	/* UI BSS List signal strength(in percentage),
	 * make it good looking, from 0~100.
	 */
	if (is_cck)
		pstatus->signalstrength = (u8)(rtl_signal_scale_mapping(hw,
			pwdb_all));
	else if (rf_rx_num != 0)
		pstatus->signalstrength = (u8)(rtl_signal_scale_mapping(hw,
			total_rssi /= rf_rx_num));
	/*HW antenna diversity*/
	rtldm->fat_table.antsel_rx_keep_0 = p_phystrpt->antidx_anta;
	rtldm->fat_table.antsel_rx_keep_1 = p_phystrpt->antidx_antb;
}