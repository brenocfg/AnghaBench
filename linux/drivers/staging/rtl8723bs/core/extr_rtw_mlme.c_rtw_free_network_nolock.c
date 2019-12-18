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
struct wlan_network {int dummy; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_free_network_nolock (int /*<<< orphan*/ *,struct wlan_network*) ; 
 int /*<<< orphan*/  rtw_cfg80211_unlink_bss (struct adapter*,struct wlan_network*) ; 

void rtw_free_network_nolock(struct adapter *padapter, struct wlan_network *pnetwork)
{
	/* RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_free_network ==> ssid = %s\n\n" , pnetwork->network.Ssid.Ssid)); */
	_rtw_free_network_nolock(&(padapter->mlmepriv), pnetwork);
	rtw_cfg80211_unlink_bss(padapter, pnetwork);
}