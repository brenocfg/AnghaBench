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
struct rx_fwinfo_8723be {int dummy; } ;
struct rtl_stats {int is_cck; int packet_matchbssid; int packet_toself; int packet_beacon; int* rx_mimo_signalquality; int rx_pwdb_all; int bt_rx_rssi_percentage; int signalquality; int* rx_mimo_signalstrength; scalar_t__ rate; int signalstrength; void* recvsignalpower; void* rxpower; void** rx_pwr; } ;
struct TYPE_4__ {int* cfo_tail; int packet_count; scalar_t__* rfpath_rxenable; } ;
struct rtl_priv {TYPE_2__ dm; } ;
struct phy_status_rpt {int cck_agc_rpt_ofdm_cfosho_a; int cck_sig_qual_ofdm_pwdb_all; scalar_t__* path_cfotail; int /*<<< orphan*/ * stream_rxevm; TYPE_1__* path_agc; } ;
struct ieee80211_hw {int dummy; } ;
typedef  void* s8 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {int gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ DESC92C_RATEMCS15 ; 
 scalar_t__ DESC92C_RATEMCS8 ; 
 int RF6052_MAX_PATH ; 
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int /*<<< orphan*/  RFPGA0_XA_HSSIPARAMETER2 ; 
 int rtl_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_get_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_query_rxpwrpercentage (void*) ; 
 scalar_t__ rtl_signal_scale_mapping (struct ieee80211_hw*,int) ; 

__attribute__((used)) static void _rtl8723be_query_rxphystatus(struct ieee80211_hw *hw,
					 struct rtl_stats *pstatus,
					 __le32 *pdesc,
					 struct rx_fwinfo_8723be *p_drvinfo,
					 bool bpacket_match_bssid,
					 bool bpacket_toself,
					 bool packet_beacon)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct phy_status_rpt *p_phystrpt = (struct phy_status_rpt *)p_drvinfo;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all, pwdb_all_bt = 0;
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

		cck_agc_rpt = p_phystrpt->cck_agc_rpt_ofdm_cfosho_a;

		/* (1)Hardware does not provide RSSI for CCK */
		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (for rate adaptive)
		 */
		cck_highpwr = (u8)rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2,
						 BIT(9));

		lan_idx = ((cck_agc_rpt & 0xE0) >> 5);
		vga_idx = (cck_agc_rpt & 0x1f);

		switch (lan_idx) {
		/* 46 53 73 95 201301231630 */
		/* 46 53 77 99 201301241630 */
		case 6:
			rx_pwr_all = -34 - (2 * vga_idx);
			break;
		case 4:
			rx_pwr_all = -14 - (2 * vga_idx);
			break;
		case 1:
			rx_pwr_all = 6 - (2 * vga_idx);
			break;
		case 0:
			rx_pwr_all = 16 - (2 * vga_idx);
			break;
		default:
			break;
		}

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		if (pwdb_all > 100)
			pwdb_all = 100;

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
		rx_pwr_all = ((p_phystrpt->cck_sig_qual_ofdm_pwdb_all >> 1) &
			     0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pwdb_all_bt = pwdb_all;
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->bt_rx_rssi_percentage = pwdb_all_bt;
		pstatus->rxpower = rx_pwr_all;
		pstatus->recvsignalpower = rx_pwr_all;

		/* (3)EVM of HT rate */
		if (pstatus->rate >= DESC92C_RATEMCS8 &&
		    pstatus->rate <= DESC92C_RATEMCS15)
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
					pstatus->signalquality =
							(u8)(evm & 0xff);
				pstatus->rx_mimo_signalquality[i] =
							(u8)(evm & 0xff);
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