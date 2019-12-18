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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtw_vif {int /*<<< orphan*/  mac_addr; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_SCAN_START ; 
 int /*<<< orphan*/  PORT_SET_MAC_ADDR ; 
 int /*<<< orphan*/  RTW_FLAG_DIG_DISABLE ; 
 int /*<<< orphan*/  RTW_FLAG_SCANNING ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_coex_scan_notify (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_flag_set (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_leave_lps (struct rtw_dev*,struct rtw_vif*) ; 
 int /*<<< orphan*/  rtw_vif_port_config (struct rtw_dev*,struct rtw_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_ops_sw_scan_start(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  const u8 *mac_addr)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;
	u32 config = 0;

	rtw_leave_lps(rtwdev, rtwvif);

	mutex_lock(&rtwdev->mutex);

	ether_addr_copy(rtwvif->mac_addr, mac_addr);
	config |= PORT_SET_MAC_ADDR;
	rtw_vif_port_config(rtwdev, rtwvif, config);

	rtw_coex_scan_notify(rtwdev, COEX_SCAN_START);

	rtw_flag_set(rtwdev, RTW_FLAG_DIG_DISABLE);
	rtw_flag_set(rtwdev, RTW_FLAG_SCANNING);

	mutex_unlock(&rtwdev->mutex);
}