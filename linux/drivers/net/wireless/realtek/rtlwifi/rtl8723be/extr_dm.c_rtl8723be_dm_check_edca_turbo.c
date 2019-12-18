#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_10__ {int txbytesunicast; int rxbytesunicast; } ;
struct TYPE_9__ {int is_any_nonbepkts; int is_cur_rdlstate; int current_turbo_edca; int /*<<< orphan*/  disable_framebursting; } ;
struct TYPE_6__ {size_t vendor; } ;
struct rtl_priv {TYPE_5__ stats; TYPE_4__ dm; TYPE_3__* cfg; TYPE_1__ mac80211; } ;
struct rtl_mac {scalar_t__ mode; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC0_BE ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 size_t PEER_ATH ; 
 size_t PEER_CISCO ; 
 size_t PEER_RAL ; 
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 size_t* edca_setting_dl ; 
 size_t* edca_setting_ul ; 
 scalar_t__ rtl8723be_dm_is_edca_turbo_disable (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8723be_dm_check_edca_turbo(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	static u64 last_txok_cnt;
	static u64 last_rxok_cnt;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;
	u32 edca_be_ul = 0x6ea42b;
	u32 edca_be_dl = 0x6ea42b;/*not sure*/
	u32 edca_be = 0x5ea42b;
	u32 iot_peer = 0;
	bool b_is_cur_rdlstate;
	bool b_bias_on_rx = false;
	bool b_edca_turbo_on = false;

	cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
	cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

	iot_peer = rtlpriv->mac80211.vendor;
	b_bias_on_rx = (iot_peer == PEER_RAL || iot_peer == PEER_ATH) ?
		       true : false;
	b_edca_turbo_on = ((!rtlpriv->dm.is_any_nonbepkts) &&
			   (!rtlpriv->dm.disable_framebursting)) ?
			   true : false;

	if ((iot_peer == PEER_CISCO) &&
	    (mac->mode == WIRELESS_MODE_N_24G)) {
		edca_be_dl = edca_setting_dl[iot_peer];
		edca_be_ul = edca_setting_ul[iot_peer];
	}
	if (rtl8723be_dm_is_edca_turbo_disable(hw))
		goto exit;

	if (b_edca_turbo_on) {
		if (b_bias_on_rx)
			b_is_cur_rdlstate = (cur_txok_cnt > cur_rxok_cnt * 4) ?
					    false : true;
		else
			b_is_cur_rdlstate = (cur_rxok_cnt > cur_txok_cnt * 4) ?
					    true : false;

		edca_be = (b_is_cur_rdlstate) ? edca_be_dl : edca_be_ul;
		rtl_write_dword(rtlpriv, REG_EDCA_BE_PARAM, edca_be);
		rtlpriv->dm.is_cur_rdlstate = b_is_cur_rdlstate;
		rtlpriv->dm.current_turbo_edca = true;
	} else {
		if (rtlpriv->dm.current_turbo_edca) {
			u8 tmp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      (u8 *)(&tmp));
		}
		rtlpriv->dm.current_turbo_edca = false;
	}

exit:
	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
}