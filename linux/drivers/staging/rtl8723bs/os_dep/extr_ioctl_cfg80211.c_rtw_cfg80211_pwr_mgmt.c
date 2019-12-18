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
struct rtw_wdev_priv {int power_mgmt; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct rtw_wdev_priv* adapter_wdev_data (struct adapter*) ; 

inline bool rtw_cfg80211_pwr_mgmt(struct adapter *adapter)
{
	struct rtw_wdev_priv *rtw_wdev_priv = adapter_wdev_data(adapter);
	return rtw_wdev_priv->power_mgmt;
}