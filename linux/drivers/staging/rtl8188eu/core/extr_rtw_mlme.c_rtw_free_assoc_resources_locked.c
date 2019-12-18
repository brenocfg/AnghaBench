#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  MacAddress; TYPE_1__ ssid; } ;
struct wlan_network {int fixed; TYPE_2__ network; } ;
struct sta_priv {int asoc_sta_count; int /*<<< orphan*/  sta_hash_lock; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {scalar_t__ key_mask; int /*<<< orphan*/  scanned_queue; struct wlan_network cur_network; } ;
struct adapter {struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_STATION_STATE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 struct wlan_network* rtw_find_network (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_all_stainfo (struct adapter*) ; 
 int /*<<< orphan*/  rtw_free_network_nolock (struct mlme_priv*,struct wlan_network*) ; 
 int /*<<< orphan*/  rtw_free_stainfo (struct adapter*,struct sta_info*) ; 
 struct sta_info* rtw_get_bcmc_stainfo (struct adapter*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_init_bcmc_stainfo (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_free_assoc_resources_locked(struct adapter *adapter)
{
	struct wlan_network *pwlan = NULL;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct sta_priv *pstapriv = &adapter->stapriv;
	struct wlan_network *tgt_network = &pmlmepriv->cur_network;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_, ("+rtw_free_assoc_resources\n"));
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_,
		 ("tgt_network->network.MacAddress=%pM ssid=%s\n",
		 tgt_network->network.MacAddress, tgt_network->network.ssid.ssid));

	if (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_AP_STATE)) {
		struct sta_info *psta;

		psta = rtw_get_stainfo(&adapter->stapriv, tgt_network->network.MacAddress);

		spin_lock_bh(&pstapriv->sta_hash_lock);
		rtw_free_stainfo(adapter,  psta);
		spin_unlock_bh(&pstapriv->sta_hash_lock);
	}

	if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE | WIFI_AP_STATE)) {
		struct sta_info *psta;

		rtw_free_all_stainfo(adapter);

		psta = rtw_get_bcmc_stainfo(adapter);
		spin_lock_bh(&pstapriv->sta_hash_lock);
		rtw_free_stainfo(adapter, psta);
		spin_unlock_bh(&pstapriv->sta_hash_lock);

		rtw_init_bcmc_stainfo(adapter);
	}

	pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
	if (pwlan)
		pwlan->fixed = false;
	else
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_free_assoc_resources:pwlan==NULL\n\n"));

	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) && (adapter->stapriv.asoc_sta_count == 1)))
		rtw_free_network_nolock(pmlmepriv, pwlan);

	pmlmepriv->key_mask = 0;
}