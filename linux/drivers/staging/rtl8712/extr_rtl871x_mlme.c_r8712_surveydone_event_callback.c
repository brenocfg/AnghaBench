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
struct wlan_bssid_ex {int /*<<< orphan*/  Ssid; int /*<<< orphan*/ * MacAddress; } ;
struct ndis_802_11_ssid {int dummy; } ;
struct mlme_priv {int to_join; int /*<<< orphan*/  lock; int /*<<< orphan*/  assoc_timer; int /*<<< orphan*/  fw_state; int /*<<< orphan*/  assoc_ssid; int /*<<< orphan*/  scan_to_timer; } ;
struct TYPE_2__ {struct wlan_bssid_ex dev_network; } ;
struct _adapter {TYPE_1__ registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_JOIN_TIMEOUT ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 int /*<<< orphan*/  _FW_UNDER_SURVEY ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_generate_random_ibss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_select_and_join_from_scan (struct mlme_priv*) ; 
 int /*<<< orphan*/  r8712_update_registrypriv_dev_network (struct _adapter*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_surveydone_event_callback(struct _adapter *adapter, u8 *pbuf)
{
	unsigned long irqL;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY)) {
		del_timer(&pmlmepriv->scan_to_timer);

		_clr_fwstate_(pmlmepriv, _FW_UNDER_SURVEY);
	}

	if (pmlmepriv->to_join) {
		if (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)) {
			if (!check_fwstate(pmlmepriv, _FW_LINKED)) {
				set_fwstate(pmlmepriv, _FW_UNDER_LINKING);

				if (!r8712_select_and_join_from_scan(pmlmepriv)) {
					mod_timer(&pmlmepriv->assoc_timer, jiffies +
						  msecs_to_jiffies(MAX_JOIN_TIMEOUT));
				} else {
					struct wlan_bssid_ex *pdev_network =
					  &(adapter->registrypriv.dev_network);
					u8 *pibss =
						 adapter->registrypriv.
							dev_network.MacAddress;
					pmlmepriv->fw_state ^= _FW_UNDER_SURVEY;
					memcpy(&pdev_network->Ssid,
						&pmlmepriv->assoc_ssid,
						sizeof(struct
							 ndis_802_11_ssid));
					r8712_update_registrypriv_dev_network
						(adapter);
					r8712_generate_random_ibss(pibss);
					pmlmepriv->fw_state =
						 WIFI_ADHOC_MASTER_STATE;
					pmlmepriv->to_join = false;
				}
			}
		} else {
			pmlmepriv->to_join = false;
			set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
			if (!r8712_select_and_join_from_scan(pmlmepriv))
				mod_timer(&pmlmepriv->assoc_timer, jiffies +
					  msecs_to_jiffies(MAX_JOIN_TIMEOUT));
			else
				_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);
		}
	}
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
}