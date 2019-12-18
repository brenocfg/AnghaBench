#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct rx_fwinfo {int dummy; } ;
struct rtl_stats {int is_cck; int packet_matchbssid; int packet_toself; int packet_beacon; int* rx_mimo_signalquality; int rx_pwdb_all; int bt_rx_rssi_percentage; int recvsignalpower; int signalquality; int* rx_pwr; int* rx_mimo_signalstrength; int rxpower; scalar_t__ rate; int signalstrength; } ;
struct TYPE_3__ {int* cfo_tail; int packet_count; scalar_t__* rfpath_rxenable; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct phy_status_rpt {int cck_agc_rpt_ofdm_cfosho_a; int cck_sig_qual_ofdm_pwdb_all; scalar_t__* path_cfotail; int /*<<< orphan*/ * stream_rxevm; TYPE_2__* path_agc; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int s8 ;
struct TYPE_4__ {int gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ DESC_RATEMCS15 ; 
 scalar_t__ DESC_RATEMCS8 ; 
 int RF6052_MAX_PATH ; 
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int /*<<< orphan*/  RFPGA0_XA_HSSIPARAMETER2 ; 
 int rtl_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_query_rxpwrpercentage (int) ; 
 scalar_t__ rtl_signal_scale_mapping (struct ieee80211_hw*,int) ; 

__attribute__((used)) static void _rtl92ee_query_rxphystatus(struct ieee80211_hw *hw,
				       struct rtl_stats *pstatus, u8 *pdesc,
				       struct rx_fwinfo *p_drvinfo,
				       bool bpacket_match_bssid,
				       bool bpacket_toself,
				       bool packet_beacon)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct phy_status_rpt *p_phystrpt = (struct phy_status_rpt *)p_drvinfo;
	s8 rx_pwr_all, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
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
		/* CCK Driver info Structure is not the same as OFDM packet. */
		cck_agc_rpt = p_phystrpt->cck_agc_rpt_ofdm_cfosho_a;

		/* (1)Hardware does not provide RSSI for CCK
		 * (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		cck_highpwr = (u8)rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2,
						 BIT(9));

		lan_idx = ((cck_agc_rpt & 0xE0) >> 5);
		vga_idx = (cck_agc_rpt & 0x1f);
		switch (lan_idx) {
		case 7: /*VGA_idx = 27~2*/
				if (vga_idx <= 27)
					rx_pwr_all = -100 + 2 * (27 - vga_idx);
				else
					rx_pwr_all = -100;
				break;
		case 6: /*VGA_idx = 2~0*/
				rx_pwr_all = -48 + 2 * (2 - vga_idx);
				break;
		case 5: /*VGA_idx = 7~5*/
				rx_pwr_all = -42 + 2 * (7 - vga_idx);
				break;
		case 4: /*VGA_idx = 7~4*/
				rx_pwr_all = -36 + 2 * (7 - vga_idx);
				break;
		case 3: /*VGA_idx = 7~0*/
				rx_pwr_all = -24 + 2 * (7 - vga_idx);
				break;
		case 2: /*VGA_idx = 5~0*/
				if (cck_highpwr)
					rx_pwr_all = -12 + 2 * (5 - vga_idx);
				else
					rx_pwr_all = -6 + 2 * (5 - vga_idx);
				break;
		case 1:
				rx_pwr_all = 8 - 2 * vga_idx;
				break;
		case 0:
				rx_pwr_all = 14 - 2 * vga_idx;
				break;
		default:
				rx_pwr_all = 0;
				break;
		}
		rx_pwr_all += 16;
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);

		if (!cck_highpwr) {
			if (pwdb_all >= 80)
				pwdb_all = ((pwdb_all - 80) << 1) +
					   ((pwdb_all - 80) >> 1) + 80;
			else if ((pwdb_all <= 78) && (pwdb_all >= 20))
				pwdb_all += 3;
			if (pwdb_all > 100)
				pwdb_all = 100;
		}

		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->bt_rx_rssi_percentage = pwdb_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3) Get Signal Quality (EVM) */
		if (bpacket_match_bssid) {
			u8 sq, sq_rpt;

			if (pstatus->rx_pwdb_all > 40) {
				sq = 100;
			} else {
				sq_rpt = p_phystrpt->cck_sig_qual_ofdm_pwdb_all;
				if (sq_rpt > 64)
					sq = 0;
				else if (sq_rpt < 20)
					sq = 100;
				else
					sq = ((64 - sq_rpt) * 100) / 44;
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

			rx_pwr[i] = ((p_phystrpt->path_agc[i].gain & 0x3f) * 2)
				    - 110;

			pstatus->rx_pwr[i] = rx_pwr[i];
			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;

			pstatus->rx_mimo_signalstrength[i] = (u8)rssi;
		}

		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		rx_pwr_all = ((p_phystrpt->cck_sig_qual_ofdm_pwdb_all >> 1)
			      & 0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->bt_rx_rssi_percentage = pwdb_all;
		pstatus->rxpower = rx_pwr_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3)EVM of HT rate */
		if (pstatus->rate >= DESC_RATEMCS8 &&
		    pstatus->rate <= DESC_RATEMCS15)
			max_spatial_stream = 2;
		else
			max_spatial_stream = 1;

		for (i = 0; i < max_spatial_stream; i++) {
			evm = rtl_evm_db_to_percentage(
						p_phystrpt->stream_rxevm[i]);

			if (bpacket_match_bssid) {
				/* Fill value in RFD, Get the first
				 * spatial stream only
				 */
				if (i == 0)
					pstatus->signalquality = (u8)(evm &
								       0xff);
				pstatus->rx_mimo_signalquality[i] = (u8)(evm &
									  0xff);
			}
		}

		if (bpacket_match_bssid) {
			for (i = RF90_PATH_A; i <= RF90_PATH_B; i++)
				rtl_priv(hw)->dm.cfo_tail[i] =
					(int)p_phystrpt->path_cfotail[i];

			if (rtl_priv(hw)->dm.packet_count == 0xffffffff)
				rtl_priv(hw)->dm.packet_count = 0;
			else
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
}