#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_14__ {scalar_t__ rxbytesunicast; scalar_t__ txbytesunicast; } ;
struct TYPE_8__ {int num_non_be_pkt; } ;
struct TYPE_13__ {int is_any_nonbepkts; int is_cur_rdlstate; int current_turbo_edca; int /*<<< orphan*/  disable_framebursting; TYPE_1__ dbginfo; } ;
struct TYPE_10__ {scalar_t__ hw_type; } ;
struct TYPE_9__ {size_t vendor; } ;
struct rtl_priv {TYPE_7__ stats; TYPE_6__ dm; TYPE_5__* cfg; TYPE_3__ rtlhal; TYPE_2__ mac80211; } ;
struct rtl_mac {scalar_t__ mode; } ;
struct rtl_dm {scalar_t__ last_rx_ok_cnt; scalar_t__ last_tx_ok_cnt; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_12__ {TYPE_4__* ops; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 size_t AC0_BE ; 
 int /*<<< orphan*/  COMP_TURBO ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DM_REG_EDCA_BE_11N ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 size_t PEER_CISCO ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 int* edca_setting_dl ; 
 int* edca_setting_ul ; 
 int /*<<< orphan*/  rtl8821ae_dm_edca_choose_traffic_idx (struct ieee80211_hw*,scalar_t__,scalar_t__,int,int*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void rtl8821ae_dm_check_edca_turbo(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_dm *rtldm =  rtl_dm(rtl_priv(hw));

	/*Keep past Tx/Rx packet count for RT-to-RT EDCA turbo.*/
	u64 cur_tx_ok_cnt = 0;
	u64 cur_rx_ok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;
	u32 edca_be = 0x5ea42b;
	u8 iot_peer = 0;
	bool *pb_is_cur_rdl_state = NULL;
	bool b_bias_on_rx = false;
	bool b_edca_turbo_on = false;

	RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
		 "rtl8821ae_dm_check_edca_turbo=====>\n");
	RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
		 "Original BE PARAM: 0x%x\n",
		 rtl_read_dword(rtlpriv, DM_REG_EDCA_BE_11N));

	if (rtlpriv->dm.dbginfo.num_non_be_pkt > 0x100)
		rtlpriv->dm.is_any_nonbepkts = true;
	rtlpriv->dm.dbginfo.num_non_be_pkt = 0;

	/*===============================
	 * list paramter for different platform
	 *===============================
	 */
	pb_is_cur_rdl_state = &rtlpriv->dm.is_cur_rdlstate;

	cur_tx_ok_cnt = rtlpriv->stats.txbytesunicast - rtldm->last_tx_ok_cnt;
	cur_rx_ok_cnt = rtlpriv->stats.rxbytesunicast - rtldm->last_rx_ok_cnt;

	rtldm->last_tx_ok_cnt = rtlpriv->stats.txbytesunicast;
	rtldm->last_rx_ok_cnt = rtlpriv->stats.rxbytesunicast;

	iot_peer = rtlpriv->mac80211.vendor;
	b_bias_on_rx = false;
	b_edca_turbo_on = ((!rtlpriv->dm.is_any_nonbepkts) &&
			   (!rtlpriv->dm.disable_framebursting)) ?
			   true : false;

	if (rtlpriv->rtlhal.hw_type != HARDWARE_TYPE_RTL8812AE) {
		if ((iot_peer == PEER_CISCO) &&
			(mac->mode == WIRELESS_MODE_N_24G)) {
			edca_be_dl = edca_setting_dl[iot_peer];
			edca_be_ul = edca_setting_ul[iot_peer];
		}
	}

	RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
		 "bIsAnyNonBEPkts : 0x%x  bDisableFrameBursting : 0x%x\n",
		 rtlpriv->dm.is_any_nonbepkts,
		 rtlpriv->dm.disable_framebursting);

	RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
		 "bEdcaTurboOn : 0x%x bBiasOnRx : 0x%x\n",
		 b_edca_turbo_on, b_bias_on_rx);

	if (b_edca_turbo_on) {
		RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
			 "curTxOkCnt : 0x%llx\n", cur_tx_ok_cnt);
		RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
			 "curRxOkCnt : 0x%llx\n", cur_rx_ok_cnt);
		if (b_bias_on_rx)
			rtl8821ae_dm_edca_choose_traffic_idx(hw, cur_tx_ok_cnt,
				cur_rx_ok_cnt, true, pb_is_cur_rdl_state);
		else
			rtl8821ae_dm_edca_choose_traffic_idx(hw, cur_tx_ok_cnt,
				cur_rx_ok_cnt, false, pb_is_cur_rdl_state);

		edca_be = (*pb_is_cur_rdl_state) ?  edca_be_dl : edca_be_ul;

		rtl_write_dword(rtlpriv, DM_REG_EDCA_BE_11N, edca_be);

		RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
			 "EDCA Turbo on: EDCA_BE:0x%x\n", edca_be);

		rtlpriv->dm.current_turbo_edca = true;

		RT_TRACE(rtlpriv, COMP_TURBO, DBG_LOUD,
			 "EDCA_BE_DL : 0x%x  EDCA_BE_UL : 0x%x  EDCA_BE : 0x%x\n",
			 edca_be_dl, edca_be_ul, edca_be);
	} else {
		if (rtlpriv->dm.current_turbo_edca) {
			u8 tmp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      (u8 *)(&tmp));
		}
		rtlpriv->dm.current_turbo_edca = false;
	}

	rtlpriv->dm.is_any_nonbepkts = false;
	rtldm->last_tx_ok_cnt = rtlpriv->stats.txbytesunicast;
	rtldm->last_rx_ok_cnt = rtlpriv->stats.rxbytesunicast;
}