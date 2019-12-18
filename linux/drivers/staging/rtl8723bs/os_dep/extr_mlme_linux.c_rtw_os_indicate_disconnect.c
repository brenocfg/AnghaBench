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
struct adapter {int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_cfg80211_indicate_disconnect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_indicate_wx_disassoc_event (struct adapter*) ; 
 int /*<<< orphan*/  rtw_reset_securitypriv_cmd (struct adapter*) ; 

void rtw_os_indicate_disconnect(struct adapter *adapter)
{
	/* RT_PMKID_LIST   backupPMKIDList[ NUM_PMKID_CACHE ]; */

	netif_carrier_off(adapter->pnetdev); /*  Do it first for tx broadcast pkt after disconnection issue! */

	rtw_cfg80211_indicate_disconnect(adapter);

	rtw_indicate_wx_disassoc_event(adapter);

	/* modify for CONFIG_IEEE80211W, none 11w also can use the same command */
	rtw_reset_securitypriv_cmd(adapter);
}