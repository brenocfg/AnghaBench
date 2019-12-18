#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int Length; int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {int join_res; int fixed; TYPE_3__ network; } ;
struct wlan_bssid_ex {int dummy; } ;
struct sta_priv {int /*<<< orphan*/  sta_hash_lock; } ;
struct sta_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ ssid_length; int /*<<< orphan*/  ssid; } ;
struct mlme_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  assoc_timer; TYPE_2__ scanned_queue; TYPE_1__ assoc_ssid; struct wlan_network cur_network; } ;
struct adapter {struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_fwstate (struct mlme_priv*) ; 
 int get_wlan_bssid_ex_sz (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct wlan_network* rtw_find_network (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_stainfo (struct adapter*,struct sta_info*) ; 
 int /*<<< orphan*/  rtw_get_encrypt_decrypt_from_registrypriv (struct adapter*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_connect (struct adapter*) ; 
 int /*<<< orphan*/  rtw_joinbss_update_network (struct adapter*,struct wlan_network*,struct wlan_network*) ; 
 struct sta_info* rtw_joinbss_update_stainfo (struct adapter*,struct wlan_network*) ; 
 int /*<<< orphan*/  rtw_reset_securitypriv (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_joinbss_event_prehandle(struct adapter *adapter, u8 *pbuf)
{
	struct sta_info *ptarget_sta = NULL, *pcur_sta = NULL;
	struct sta_priv *pstapriv = &adapter->stapriv;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct wlan_network *pnetwork = (struct wlan_network *)pbuf;
	struct wlan_network *cur_network = &pmlmepriv->cur_network;
	struct wlan_network *pcur_wlan = NULL, *ptarget_wlan = NULL;
	unsigned int the_same_macaddr = false;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("joinbss event call back received with res=%d\n", pnetwork->join_res));

	rtw_get_encrypt_decrypt_from_registrypriv(adapter);

	if (pmlmepriv->assoc_ssid.ssid_length == 0)
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("@@@@@   joinbss event call back  for Any SSid\n"));
	else
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("@@@@@   rtw_joinbss_event_callback for SSid:%s\n", pmlmepriv->assoc_ssid.ssid));

	the_same_macaddr = !memcmp(pnetwork->network.MacAddress, cur_network->network.MacAddress, ETH_ALEN);

	pnetwork->network.Length = get_wlan_bssid_ex_sz(&pnetwork->network);
	if (pnetwork->network.Length > sizeof(struct wlan_bssid_ex)) {
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("\n\n ***joinbss_evt_callback return a wrong bss ***\n\n"));
		return;
	}

	spin_lock_bh(&pmlmepriv->lock);

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("\nrtw_joinbss_event_callback!! _enter_critical\n"));

	if (pnetwork->join_res > 0) {
		spin_lock_bh(&pmlmepriv->scanned_queue.lock);
		if (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) {
			/* s1. find ptarget_wlan */
			if (check_fwstate(pmlmepriv, _FW_LINKED)) {
				if (the_same_macaddr) {
					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
				} else {
					pcur_wlan = rtw_find_network(&pmlmepriv->scanned_queue, cur_network->network.MacAddress);
					if (pcur_wlan)
						pcur_wlan->fixed = false;

					pcur_sta = rtw_get_stainfo(pstapriv, cur_network->network.MacAddress);
					if (pcur_sta) {
						spin_lock_bh(&pstapriv->sta_hash_lock);
						rtw_free_stainfo(adapter,  pcur_sta);
						spin_unlock_bh(&pstapriv->sta_hash_lock);
					}

					ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
					if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
						if (ptarget_wlan)
							ptarget_wlan->fixed = true;
					}
				}
			} else {
				ptarget_wlan = rtw_find_network(&pmlmepriv->scanned_queue, pnetwork->network.MacAddress);
				if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
					if (ptarget_wlan)
						ptarget_wlan->fixed = true;
				}
			}

			/* s2. update cur_network */
			if (ptarget_wlan) {
				rtw_joinbss_update_network(adapter, ptarget_wlan, pnetwork);
			} else {
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Can't find ptarget_wlan when joinbss_event callback\n"));
				spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
				goto ignore_joinbss_callback;
			}

			/* s3. find ptarget_sta & update ptarget_sta after update cur_network only for station mode */
			if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
				ptarget_sta = rtw_joinbss_update_stainfo(adapter, pnetwork);
				if (!ptarget_sta) {
					RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("Can't update stainfo when joinbss_event callback\n"));
					spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
					goto ignore_joinbss_callback;
				}
			}

			/* s4. indicate connect */
			if (check_fwstate(pmlmepriv, WIFI_STATION_STATE)) {
				rtw_indicate_connect(adapter);
			} else {
				/* adhoc mode will rtw_indicate_connect when rtw_stassoc_event_callback */
				RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("adhoc mode, fw_state:%x", get_fwstate(pmlmepriv)));
			}

			/* s5. Cancel assoc_timer */
			del_timer_sync(&pmlmepriv->assoc_timer);

			RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("Cancel assoc_timer\n"));

		} else {
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_joinbss_event_callback err: fw_state:%x", get_fwstate(pmlmepriv)));
			spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
			goto ignore_joinbss_callback;
		}

		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);

	} else if (pnetwork->join_res == -4) {
		rtw_reset_securitypriv(adapter);
		mod_timer(&pmlmepriv->assoc_timer,
			  jiffies + msecs_to_jiffies(1));

		if (check_fwstate(pmlmepriv, _FW_UNDER_LINKING)) {
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("fail! clear _FW_UNDER_LINKING ^^^fw_state=%x\n", get_fwstate(pmlmepriv)));
			_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
		}
	} else { /* if join_res < 0 (join fails), then try again */
		mod_timer(&pmlmepriv->assoc_timer,
			  jiffies + msecs_to_jiffies(1));
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
	}

ignore_joinbss_callback:
	spin_unlock_bh(&pmlmepriv->lock);
}