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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int load_imrandiqk_setting_for2g; } ;
struct TYPE_11__ {scalar_t__ supp_phymode_switch; } ;
struct TYPE_10__ {TYPE_2__* btc_ops; } ;
struct TYPE_8__ {scalar_t__ higher_busytraffic; } ;
struct rtl_priv {TYPE_7__* cfg; TYPE_5__ rtlhal; TYPE_4__ dm; TYPE_3__ btcoexist; TYPE_1__ link_info; } ;
struct rtl_mac {int act_scanning; int skip_scan; scalar_t__ link_state; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_14__ {TYPE_6__* ops; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* scan_operation_backup ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* chk_switch_dmdp ) (struct ieee80211_hw*) ;scalar_t__ (* get_btc_status ) () ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* btc_scan_notify_wifi_only ) (struct rtl_priv*,int) ;int /*<<< orphan*/  (* btc_scan_notify ) (struct rtl_priv*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  LED_CTL_SITE_SURVEY ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MAC80211_LINKED_SCANNING ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCAN_OPT_BACKUP_BAND0 ; 
 int /*<<< orphan*/  rtl_ips_nic_on (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_lps_leave (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_op_sw_scan_start(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 const u8 *mac_addr)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, "\n");
	mac->act_scanning = true;
	if (rtlpriv->link_info.higher_busytraffic) {
		mac->skip_scan = true;
		return;
	}

	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_scan_notify(rtlpriv, 1);
	else if (rtlpriv->btcoexist.btc_ops)
		rtlpriv->btcoexist.btc_ops->btc_scan_notify_wifi_only(rtlpriv,
								      1);

	if (rtlpriv->dm.supp_phymode_switch) {
		if (rtlpriv->cfg->ops->chk_switch_dmdp)
			rtlpriv->cfg->ops->chk_switch_dmdp(hw);
	}

	if (mac->link_state == MAC80211_LINKED) {
		rtl_lps_leave(hw);
		mac->link_state = MAC80211_LINKED_SCANNING;
	} else {
		rtl_ips_nic_on(hw);
	}

	/* Dul mac */
	rtlpriv->rtlhal.load_imrandiqk_setting_for2g = false;

	rtlpriv->cfg->ops->led_control(hw, LED_CTL_SITE_SURVEY);
	rtlpriv->cfg->ops->scan_operation_backup(hw, SCAN_OPT_BACKUP_BAND0);
}