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
struct rx_fwinfo_92c {int* cfosho; int* gain_trsw; int* rxsnr; int pwdb_all; int /*<<< orphan*/ * rxevm; } ;
struct rx_desc_92c {int /*<<< orphan*/  rxmcs; } ;
struct rtl_stats {int packet_matchbssid; int packet_toself; int packet_beacon; int is_cck; int* RX_SIGQ; int rx_pwdb_all; int signalquality; int* rx_mimo_signalstrength; int signalstrength; void* recvsignalpower; void* rxpower; } ;
struct TYPE_4__ {long* rx_snr_db; } ;
struct TYPE_3__ {int* rfpath_rxenable; } ;
struct rtl_phy {int cck_high_power; } ;
struct rtl_priv {TYPE_2__ stats; TYPE_1__ dm; struct rtl_phy phy; } ;
struct phy_sts_cck_8192s_t {int cck_agc_rpt; int sq_rpt; } ;
struct ieee80211_hw {int dummy; } ;
typedef  void* s8 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ DESC_RATEMCS15 ; 
 scalar_t__ DESC_RATEMCS8 ; 
 int RF90_PATH_A ; 
 int RF90_PATH_MAX ; 
 int RX_HAL_IS_CCK_RATE (int /*<<< orphan*/ ) ; 
 int _rtl92c_query_rxpwrpercentage (void*) ; 
 scalar_t__ _rtl92c_signal_scale_mapping (struct ieee80211_hw*,int) ; 
 scalar_t__ get_rx_desc_rx_mcs (int /*<<< orphan*/ *) ; 
 int rtl_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92c_query_rxphystatus(struct ieee80211_hw *hw,
				      struct rtl_stats *pstats,
				      struct rx_desc_92c *p_desc,
				      struct rx_fwinfo_92c *p_drvinfo,
				      bool packet_match_bssid,
				      bool packet_toself,
				      bool packet_beacon)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct phy_sts_cck_8192s_t *cck_buf;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool in_powersavemode = false;
	bool is_cck_rate;
	__le32 *pdesc = (__le32 *)p_desc;

	is_cck_rate = RX_HAL_IS_CCK_RATE(p_desc->rxmcs);
	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_toself = packet_toself;
	pstats->packet_beacon = packet_beacon;
	pstats->is_cck = is_cck_rate;
	pstats->RX_SIGQ[0] = -1;
	pstats->RX_SIGQ[1] = -1;
	if (is_cck_rate) {
		u8 report, cck_highpwr;

		cck_buf = (struct phy_sts_cck_8192s_t *)p_drvinfo;
		if (!in_powersavemode)
			cck_highpwr = rtlphy->cck_high_power;
		else
			cck_highpwr = false;
		if (!cck_highpwr) {
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;

			report = cck_buf->cck_agc_rpt & 0xc0;
			report = report >> 6;
			switch (report) {
			case 0x3:
				rx_pwr_all = -46 - (cck_agc_rpt & 0x3e);
				break;
			case 0x2:
				rx_pwr_all = -26 - (cck_agc_rpt & 0x3e);
				break;
			case 0x1:
				rx_pwr_all = -12 - (cck_agc_rpt & 0x3e);
				break;
			case 0x0:
				rx_pwr_all = 16 - (cck_agc_rpt & 0x3e);
				break;
			}
		} else {
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;

			report = p_drvinfo->cfosho[0] & 0x60;
			report = report >> 5;
			switch (report) {
			case 0x3:
				rx_pwr_all = -46 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			case 0x2:
				rx_pwr_all = -26 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			case 0x1:
				rx_pwr_all = -12 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			case 0x0:
				rx_pwr_all = 16 - ((cck_agc_rpt & 0x1f) << 1);
				break;
			}
		}
		pwdb_all = _rtl92c_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->recvsignalpower = rx_pwr_all;
		if (packet_match_bssid) {
			u8 sq;

			if (pstats->rx_pwdb_all > 40)
				sq = 100;
			else {
				sq = cck_buf->sq_rpt;
				if (sq > 64)
					sq = 0;
				else if (sq < 20)
					sq = 100;
				else
					sq = ((64 - sq) * 100) / 44;
			}
			pstats->signalquality = sq;
			pstats->RX_SIGQ[0] = sq;
			pstats->RX_SIGQ[1] = -1;
		}
	} else {
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
		for (i = RF90_PATH_A; i < RF90_PATH_MAX; i++) {
			if (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;
			rx_pwr[i] =
			    ((p_drvinfo->gain_trsw[i] & 0x3f) * 2) - 110;
			rssi = _rtl92c_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;
			rtlpriv->stats.rx_snr_db[i] =
			    (long)(p_drvinfo->rxsnr[i] / 2);

			if (packet_match_bssid)
				pstats->rx_mimo_signalstrength[i] = (u8) rssi;
		}
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;
		pwdb_all = _rtl92c_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->rxpower = rx_pwr_all;
		pstats->recvsignalpower = rx_pwr_all;
		if (get_rx_desc_rx_mcs(pdesc) &&
		    get_rx_desc_rx_mcs(pdesc) >= DESC_RATEMCS8 &&
		    get_rx_desc_rx_mcs(pdesc) <= DESC_RATEMCS15)
			max_spatial_stream = 2;
		else
			max_spatial_stream = 1;
		for (i = 0; i < max_spatial_stream; i++) {
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);
			if (packet_match_bssid) {
				if (i == 0)
					pstats->signalquality =
					    (u8) (evm & 0xff);
				pstats->RX_SIGQ[i] =
				    (u8) (evm & 0xff);
			}
		}
	}
	if (is_cck_rate)
		pstats->signalstrength =
		    (u8) (_rtl92c_signal_scale_mapping(hw, pwdb_all));
	else if (rf_rx_num != 0)
		pstats->signalstrength =
		    (u8) (_rtl92c_signal_scale_mapping
			  (hw, total_rssi /= rf_rx_num));
}