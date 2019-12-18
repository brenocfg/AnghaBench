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
struct rtw_vif {scalar_t__ bcn_ctrl; int /*<<< orphan*/  net_type; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  port; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_SET_BCN_CTRL ; 
 int /*<<< orphan*/  PORT_SET_MAC_ADDR ; 
 int /*<<< orphan*/  PORT_SET_NET_TYPE ; 
 int /*<<< orphan*/  RTW_NET_NO_LINK ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_info (struct rtw_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_vif_port_config (struct rtw_dev*,struct rtw_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_ops_remove_interface(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_vif *rtwvif = (struct rtw_vif *)vif->drv_priv;
	u32 config = 0;

	rtw_info(rtwdev, "stop vif %pM on port %d\n", vif->addr, rtwvif->port);

	mutex_lock(&rtwdev->mutex);

	eth_zero_addr(rtwvif->mac_addr);
	config |= PORT_SET_MAC_ADDR;
	rtwvif->net_type = RTW_NET_NO_LINK;
	config |= PORT_SET_NET_TYPE;
	rtwvif->bcn_ctrl = 0;
	config |= PORT_SET_BCN_CTRL;
	rtw_vif_port_config(rtwdev, rtwvif, config);

	mutex_unlock(&rtwdev->mutex);
}