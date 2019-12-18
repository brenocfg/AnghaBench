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
typedef  int u8 ;
struct wlan_bssid_ex {int* MacAddress; int /*<<< orphan*/  ssid; } ;
struct ndis_802_11_ssid {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bBusyTraffic; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {int join_res; } ;
struct mlme_priv {int to_join; scalar_t__ to_roaming; int /*<<< orphan*/  assoc_ssid; TYPE_3__ LinkDetectInfo; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  assoc_timer; struct __queue scanned_queue; struct list_head* pscanned; TYPE_1__ cur_network; } ;
struct list_head {struct list_head* next; } ;
struct TYPE_5__ {struct wlan_bssid_ex dev_network; } ;
struct adapter {TYPE_2__ registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_JOIN_TIMEOUT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int _FAIL ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 struct list_head* get_list_head (struct __queue*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int rtw_createbss_cmd (struct adapter*) ; 
 int /*<<< orphan*/  rtw_generate_random_ibss (int*) ; 
 int rtw_select_and_join_from_scanned_queue (struct mlme_priv*) ; 
 int rtw_sitesurvey_cmd (struct adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_update_registrypriv_dev_network (struct adapter*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u8 rtw_do_join(struct adapter *padapter)
{
	struct list_head *plist, *phead;
	u8 *pibss = NULL;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct __queue *queue = &pmlmepriv->scanned_queue;
	u8 ret = _SUCCESS;

	spin_lock_bh(&pmlmepriv->scanned_queue.lock);
	phead = get_list_head(queue);
	plist = phead->next;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("\n rtw_do_join: phead = %p; plist = %p\n\n\n", phead, plist));

	pmlmepriv->cur_network.join_res = -2;

	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

	pmlmepriv->pscanned = plist;

	pmlmepriv->to_join = true;

	if (list_empty(&queue->queue)) {
		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		/* when set_ssid/set_bssid for rtw_do_join(), but scanning queue is empty */
		/* we try to issue sitesurvey firstly */

		if (!pmlmepriv->LinkDetectInfo.bBusyTraffic ||
		    pmlmepriv->to_roaming > 0) {
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("rtw_do_join(): site survey if scanned_queue is empty\n."));
			/*  submit site_survey_cmd */
			ret = rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, NULL, 0);
			if (ret != _SUCCESS) {
				pmlmepriv->to_join = false;
				RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("rtw_do_join(): site survey return error\n."));
			}
		} else {
			pmlmepriv->to_join = false;
			ret = _FAIL;
		}

		goto exit;
	} else {
		int select_ret;

		spin_unlock_bh(&pmlmepriv->scanned_queue.lock);
		select_ret = rtw_select_and_join_from_scanned_queue(pmlmepriv);
		if (select_ret == _SUCCESS) {
			pmlmepriv->to_join = false;
			mod_timer(&pmlmepriv->assoc_timer,
				  jiffies + msecs_to_jiffies(MAX_JOIN_TIMEOUT));
		} else {
			if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) {
				/*  submit createbss_cmd to change to a ADHOC_MASTER */

				/* pmlmepriv->lock has been acquired by caller... */
				struct wlan_bssid_ex    *pdev_network = &padapter->registrypriv.dev_network;

				pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;

				pibss = padapter->registrypriv.dev_network.MacAddress;

				memcpy(&pdev_network->ssid, &pmlmepriv->assoc_ssid, sizeof(struct ndis_802_11_ssid));

				rtw_update_registrypriv_dev_network(padapter);

				rtw_generate_random_ibss(pibss);

				if (rtw_createbss_cmd(padapter) != _SUCCESS) {
					RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("***Error =>do_goin: rtw_createbss_cmd status FAIL***\n "));
					ret =  false;
					goto exit;
				}
				pmlmepriv->to_join = false;

				RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_,
					 ("***Error => rtw_select_and_join_from_scanned_queue FAIL under STA_Mode***\n "));
			} else {
				/*  can't associate ; reset under-linking */
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

				/* when set_ssid/set_bssid for rtw_do_join(), but there are no desired bss in scanning queue */
				/* we try to issue sitesurvey firstly */
				if (!pmlmepriv->LinkDetectInfo.bBusyTraffic ||
				    pmlmepriv->to_roaming > 0) {
					ret = rtw_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid, 1, NULL, 0);
					if (ret != _SUCCESS) {
						pmlmepriv->to_join = false;
						RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("do_join(): site survey return error\n."));
					}
				} else {
					ret = _FAIL;
					pmlmepriv->to_join = false;
				}
			}
		}
	}

exit:
	return ret;
}