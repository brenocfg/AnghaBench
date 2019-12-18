#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rtw_vif {int /*<<< orphan*/  mac_addr; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_SCAN_FINISH ; 
 int /*<<< orphan*/  PORT_SET_MAC_ADDR ; 
 int /*<<< orphan*/  RTW_FLAG_DIG_DISABLE ; 
 int /*<<< orphan*/  RTW_FLAG_SCANNING ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_coex_scan_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_flag_clear (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_vif_port_config (struct rtw_dev*,struct rtw_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_ops_sw_scan_complete(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;
	u32 config = 0;

	mutex_lock(&rtwdev->mutex);

	rtw_flag_clear(rtwdev, RTW_FLAG_SCANNING);
	rtw_flag_clear(rtwdev, RTW_FLAG_DIG_DISABLE);

	ether_addr_copy(rtwvif->mac_addr, vif->addr);
	config |= PORT_SET_MAC_ADDR;
	rtw_vif_port_config(rtwdev, rtwvif, config);

	rtw_coex_scan_notify(rtwdev, COEX_SCAN_FINISH);

	mutex_unlock(&rtwdev->mutex);
}