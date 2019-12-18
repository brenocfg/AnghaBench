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
typedef  int /*<<< orphan*/  u8 ;
struct wlan_network {int /*<<< orphan*/  network; int /*<<< orphan*/  list; int /*<<< orphan*/  last_scanned; } ;
struct wlan_bssid_ex {int /*<<< orphan*/  Length; int /*<<< orphan*/  MacAddress; } ;
struct sta_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_1__ scanned_queue; int /*<<< orphan*/  assoc_timer; struct wlan_network cur_network; } ;
struct cmd_obj {scalar_t__ res; int /*<<< orphan*/ * parmbuf; } ;
struct adapter {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _cancel_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wlan_bssid_ex*,int /*<<< orphan*/ ) ; 
 struct wlan_network* rtw_alloc_network (struct mlme_priv*) ; 
 struct sta_info* rtw_alloc_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 
 struct wlan_network* rtw_get_oldest_wlan_network (TYPE_1__*) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_indicate_connect (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void rtw_createbss_cmd_callback(struct adapter *padapter, struct cmd_obj *pcmd)
{
	u8 timer_cancelled;
	struct sta_info *psta = NULL;
	struct wlan_network *pwlan = NULL;
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct wlan_bssid_ex *pnetwork = (struct wlan_bssid_ex *)pcmd->parmbuf;
	struct wlan_network *tgt_network = &(pmlmepriv->cur_network);

	if (pcmd->parmbuf == NULL)
		goto exit;

	if ((pcmd->res != H2C_SUCCESS)) {
		RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\n ********Error: rtw_createbss_cmd_callback  Fail ************\n\n."));
		_set_timer(&pmlmepriv->assoc_timer, 1);
	}

	_cancel_timer(&pmlmepriv->assoc_timer, &timer_cancelled);

	spin_lock_bh(&pmlmepriv->lock);


	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		psta = rtw_get_stainfo(&padapter->stapriv, pnetwork->MacAddress);
		if (!psta) {
			psta = rtw_alloc_stainfo(&padapter->stapriv, pnetwork->MacAddress);
			if (psta == NULL) {
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\nCan't alloc sta_info when createbss_cmd_callback\n"));
				goto createbss_cmd_fail;
			}
		}

		rtw_indicate_connect(padapter);
	} else {
		pwlan = rtw_alloc_network(pmlmepriv);
		spin_lock_bh(&(pmlmepriv->scanned_queue.lock));
		if (pwlan == NULL) {
			pwlan = rtw_get_oldest_wlan_network(&pmlmepriv->scanned_queue);
			if (pwlan == NULL) {
				RT_TRACE(_module_rtl871x_cmd_c_, _drv_err_, ("\n Error:  can't get pwlan in rtw_joinbss_event_callback\n"));
				spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
				goto createbss_cmd_fail;
			}
			pwlan->last_scanned = jiffies;
		} else {
			list_add_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue);
		}

		pnetwork->Length = get_wlan_bssid_ex_sz(pnetwork);
		memcpy(&(pwlan->network), pnetwork, pnetwork->Length);
		/* pwlan->fixed = true; */

		/* list_add_tail(&(pwlan->list), &pmlmepriv->scanned_queue.queue); */

		/*  copy pdev_network information to	pmlmepriv->cur_network */
		memcpy(&tgt_network->network, pnetwork, (get_wlan_bssid_ex_sz(pnetwork)));

		/*  reset DSConfig */
		/* tgt_network->network.Configuration.DSConfig = (u32)rtw_ch2freq(pnetwork->Configuration.DSConfig); */

		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

		spin_unlock_bh(&(pmlmepriv->scanned_queue.lock));
		/*  we will set _FW_LINKED when there is one more sat to join us (rtw_stassoc_event_callback) */

	}

createbss_cmd_fail:

	spin_unlock_bh(&pmlmepriv->lock);
exit:
	rtw_free_cmd_obj(pcmd);
}