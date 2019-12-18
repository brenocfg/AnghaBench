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
struct mlme_priv {int dummy; } ;
struct adapter {scalar_t__* pid; int /*<<< orphan*/  pnetdev; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_cfg80211_ibss_indicate_connect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_cfg80211_indicate_connect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_indicate_wx_assoc_event (struct adapter*) ; 
 int /*<<< orphan*/  rtw_signal_process (scalar_t__,int /*<<< orphan*/ ) ; 

void rtw_os_indicate_connect(struct adapter *adapter)
{
	struct mlme_priv *pmlmepriv = &(adapter->mlmepriv);

	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) {
		rtw_cfg80211_ibss_indicate_connect(adapter);
	} else
		rtw_cfg80211_indicate_connect(adapter);

	rtw_indicate_wx_assoc_event(adapter);
	netif_carrier_on(adapter->pnetdev);

	if (adapter->pid[2] != 0)
		rtw_signal_process(adapter->pid[2], SIGALRM);
}