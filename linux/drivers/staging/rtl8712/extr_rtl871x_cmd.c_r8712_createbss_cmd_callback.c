#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlan_network {int fixed; int /*<<< orphan*/  network; int /*<<< orphan*/  list; scalar_t__ last_scanned; } ;
struct TYPE_6__ {void* Length; void* HopSet; void* HopPattern; void* DwellTime; } ;
struct TYPE_7__ {void* Length; TYPE_2__ FHConfig; void* DSConfig; void* ATIMWindow; } ;
struct TYPE_5__ {void* SsidLength; } ;
struct wlan_bssid_ex {void* Length; int /*<<< orphan*/  MacAddress; void* IELength; void* InfrastructureMode; TYPE_3__ Configuration; void* NetworkTypeInUse; void* Rssi; void* Privacy; TYPE_1__ Ssid; } ;
struct sta_info {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue; } ;
struct mlme_priv {int fw_state; int /*<<< orphan*/  lock; TYPE_4__ scanned_queue; int /*<<< orphan*/  assoc_timer; struct wlan_network cur_network; } ;
struct cmd_obj {scalar_t__ res; scalar_t__ parmbuf; } ;
struct _adapter {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int WIFI_AP_STATE ; 
 int _FW_UNDER_LINKING ; 
 struct wlan_network* _r8712_alloc_network (struct mlme_priv*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 void* le32_to_cpu (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wlan_bssid_ex*,void*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct sta_info* r8712_alloc_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_free_cmd_obj (struct cmd_obj*) ; 
 struct wlan_network* r8712_get_oldest_wlan_network (TYPE_4__*) ; 
 struct sta_info* r8712_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* r8712_get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  r8712_indicate_connect (struct _adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_createbss_cmd_callback(struct _adapter *padapter,
				  struct cmd_obj *pcmd)
{
	unsigned long irqL;
	struct sta_info *psta = NULL;
	struct wlan_network *pwlan = NULL;
	struct	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct wlan_bssid_ex *pnetwork = (struct wlan_bssid_ex *)pcmd->parmbuf;
	struct wlan_network *tgt_network = &(pmlmepriv->cur_network);

	if (pcmd->res != H2C_SUCCESS)
		mod_timer(&pmlmepriv->assoc_timer,
			  jiffies + msecs_to_jiffies(1));
	del_timer(&pmlmepriv->assoc_timer);
#ifdef __BIG_ENDIAN
	/* endian_convert */
	pnetwork->Length = le32_to_cpu(pnetwork->Length);
	pnetwork->Ssid.SsidLength = le32_to_cpu(pnetwork->Ssid.SsidLength);
	pnetwork->Privacy = le32_to_cpu(pnetwork->Privacy);
	pnetwork->Rssi = le32_to_cpu(pnetwork->Rssi);
	pnetwork->NetworkTypeInUse = le32_to_cpu(pnetwork->NetworkTypeInUse);
	pnetwork->Configuration.ATIMWindow =
		le32_to_cpu(pnetwork->Configuration.ATIMWindow);
	pnetwork->Configuration.DSConfig =
		le32_to_cpu(pnetwork->Configuration.DSConfig);
	pnetwork->Configuration.FHConfig.DwellTime =
		le32_to_cpu(pnetwork->Configuration.FHConfig.DwellTime);
	pnetwork->Configuration.FHConfig.HopPattern =
		le32_to_cpu(pnetwork->Configuration.FHConfig.HopPattern);
	pnetwork->Configuration.FHConfig.HopSet =
		le32_to_cpu(pnetwork->Configuration.FHConfig.HopSet);
	pnetwork->Configuration.FHConfig.Length =
		le32_to_cpu(pnetwork->Configuration.FHConfig.Length);
	pnetwork->Configuration.Length =
		le32_to_cpu(pnetwork->Configuration.Length);
	pnetwork->InfrastructureMode =
		le32_to_cpu(pnetwork->InfrastructureMode);
	pnetwork->IELength = le32_to_cpu(pnetwork->IELength);
#endif
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if ((pmlmepriv->fw_state) & WIFI_AP_STATE) {
		psta = r8712_get_stainfo(&padapter->stapriv,
					 pnetwork->MacAddress);
		if (!psta) {
			psta = r8712_alloc_stainfo(&padapter->stapriv,
						   pnetwork->MacAddress);
			if (!psta)
				goto createbss_cmd_fail;
		}
		r8712_indicate_connect(padapter);
	} else {
		pwlan = _r8712_alloc_network(pmlmepriv);
		if (!pwlan) {
			pwlan = r8712_get_oldest_wlan_network(
				&pmlmepriv->scanned_queue);
			if (!pwlan)
				goto createbss_cmd_fail;
			pwlan->last_scanned = jiffies;
		} else {
			list_add_tail(&(pwlan->list),
					 &pmlmepriv->scanned_queue.queue);
		}
		pnetwork->Length = r8712_get_wlan_bssid_ex_sz(pnetwork);
		memcpy(&(pwlan->network), pnetwork, pnetwork->Length);
		pwlan->fixed = true;
		memcpy(&tgt_network->network, pnetwork,
			(r8712_get_wlan_bssid_ex_sz(pnetwork)));
		if (pmlmepriv->fw_state & _FW_UNDER_LINKING)
			pmlmepriv->fw_state ^= _FW_UNDER_LINKING;
		/*
		 * we will set _FW_LINKED when there is one more sat to
		 * join us (stassoc_event_callback)
		 */
	}
createbss_cmd_fail:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	r8712_free_cmd_obj(pcmd);
}