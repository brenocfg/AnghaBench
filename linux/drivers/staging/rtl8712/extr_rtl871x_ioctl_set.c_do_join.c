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
struct wlan_bssid_ex {int* MacAddress; int /*<<< orphan*/  Ssid; } ;
struct ndis_802_11_ssid {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  traffic_busy; } ;
struct TYPE_4__ {int join_res; } ;
struct list_head {struct list_head* next; } ;
struct __queue {struct list_head queue; } ;
struct mlme_priv {int fw_state; int to_join; int /*<<< orphan*/  assoc_ssid; TYPE_3__ sitesurveyctrl; int /*<<< orphan*/  assoc_timer; struct list_head* pscanned; TYPE_1__ cur_network; struct __queue scanned_queue; } ;
struct TYPE_5__ {struct wlan_bssid_ex dev_network; } ;
struct _adapter {TYPE_2__ registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_JOIN_TIMEOUT ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int _FW_UNDER_LINKING ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ r8712_createbss_cmd (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_generate_random_ibss (int*) ; 
 int r8712_select_and_join_from_scan (struct mlme_priv*) ; 
 int /*<<< orphan*/  r8712_sitesurvey_cmd (struct _adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_update_registrypriv_dev_network (struct _adapter*) ; 

__attribute__((used)) static u8 do_join(struct _adapter *padapter)
{
	struct list_head *plist, *phead;
	u8 *pibss = NULL;
	struct	mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct  __queue	*queue	= &(pmlmepriv->scanned_queue);
	int ret;

	phead = &queue->queue;
	plist = phead->next;
	pmlmepriv->cur_network.join_res = -2;
	pmlmepriv->fw_state |= _FW_UNDER_LINKING;
	pmlmepriv->pscanned = plist;
	pmlmepriv->to_join = true;

	/* adhoc mode will start with an empty queue, but skip checking */
	if (!check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) &&
	    list_empty(&queue->queue)) {
		if (pmlmepriv->fw_state & _FW_UNDER_LINKING)
			pmlmepriv->fw_state ^= _FW_UNDER_LINKING;
		/* when set_ssid/set_bssid for do_join(), but scanning queue
		 * is empty we try to issue sitesurvey firstly
		 */
		if (!pmlmepriv->sitesurveyctrl.traffic_busy)
			r8712_sitesurvey_cmd(padapter, &pmlmepriv->assoc_ssid);
		return true;
	}

	ret = r8712_select_and_join_from_scan(pmlmepriv);
	if (!ret) {
		mod_timer(&pmlmepriv->assoc_timer,
			  jiffies + msecs_to_jiffies(MAX_JOIN_TIMEOUT));
	} else {
		if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) {
			/* submit r8712_createbss_cmd to change to an
			 * ADHOC_MASTER pmlmepriv->lock has been
			 * acquired by caller...
			 */
			struct wlan_bssid_ex *pdev_network =
				&(padapter->registrypriv.dev_network);
			pmlmepriv->fw_state = WIFI_ADHOC_MASTER_STATE;
			pibss = padapter->registrypriv.dev_network.MacAddress;
			memcpy(&pdev_network->Ssid,
			       &pmlmepriv->assoc_ssid,
			       sizeof(struct ndis_802_11_ssid));
			r8712_update_registrypriv_dev_network(padapter);
			r8712_generate_random_ibss(pibss);
			if (r8712_createbss_cmd(padapter))
				return false;
			pmlmepriv->to_join = false;
		} else {
			/* can't associate ; reset under-linking */
			if (pmlmepriv->fw_state & _FW_UNDER_LINKING)
				pmlmepriv->fw_state ^=
					_FW_UNDER_LINKING;
			/* when set_ssid/set_bssid for do_join(), but
			 * there are no desired bss in scanning queue
			 * we try to issue sitesurvey first
			 */
			if (!pmlmepriv->sitesurveyctrl.traffic_busy)
				r8712_sitesurvey_cmd(padapter,
						     &pmlmepriv->assoc_ssid);
		}
	}
	return true;
}