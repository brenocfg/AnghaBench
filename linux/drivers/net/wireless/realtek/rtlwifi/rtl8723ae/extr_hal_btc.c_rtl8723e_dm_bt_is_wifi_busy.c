#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tx_busy_traffic; scalar_t__ rx_busy_traffic; scalar_t__ busytraffic; } ;
struct rtl_priv {TYPE_1__ link_info; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool rtl8723e_dm_bt_is_wifi_busy(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	if (rtlpriv->link_info.busytraffic ||
		rtlpriv->link_info.rx_busy_traffic ||
		rtlpriv->link_info.tx_busy_traffic)
		return true;
	else
		return false;
}