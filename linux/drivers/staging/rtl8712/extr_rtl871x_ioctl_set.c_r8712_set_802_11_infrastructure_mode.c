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
struct TYPE_2__ {int InfrastructureMode; } ;
struct wlan_network {TYPE_1__ network; } ;
struct mlme_priv {int /*<<< orphan*/  lock; struct wlan_network cur_network; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;
typedef  enum NDIS_802_11_NETWORK_INFRASTRUCTURE { ____Placeholder_NDIS_802_11_NETWORK_INFRASTRUCTURE } NDIS_802_11_NETWORK_INFRASTRUCTURE ;

/* Variables and functions */
#define  Ndis802_11APMode 132 
#define  Ndis802_11AutoUnknown 131 
#define  Ndis802_11IBSS 130 
#define  Ndis802_11Infrastructure 129 
#define  Ndis802_11InfrastructureMax 128 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_STATION_STATE ; 
 int _FW_LINKED ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  r8712_disassoc_cmd (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_assoc_resources (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_ind_disconnect (struct _adapter*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_set_802_11_infrastructure_mode(struct _adapter *padapter,
	enum NDIS_802_11_NETWORK_INFRASTRUCTURE networktype)
{
	unsigned long irqL;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct wlan_network	*cur_network = &pmlmepriv->cur_network;
	enum NDIS_802_11_NETWORK_INFRASTRUCTURE *pold_state =
				&(cur_network->network.InfrastructureMode);

	if (*pold_state != networktype) {
		spin_lock_irqsave(&pmlmepriv->lock, irqL);
		if (check_fwstate(pmlmepriv, _FW_LINKED) ||
		    (*pold_state == Ndis802_11IBSS))
			r8712_disassoc_cmd(padapter);
		if (check_fwstate(pmlmepriv,
		    _FW_LINKED | WIFI_ADHOC_MASTER_STATE))
			r8712_free_assoc_resources(padapter);
		if (check_fwstate(pmlmepriv, _FW_LINKED) ||
		    (*pold_state == Ndis802_11Infrastructure) ||
		    (*pold_state == Ndis802_11IBSS)) {
			/* will clr Linked_state before this function,
			 * we must have checked whether issue dis-assoc_cmd or
			 * not
			 */
			r8712_ind_disconnect(padapter);
		}
		*pold_state = networktype;
		/* clear WIFI_STATION_STATE; WIFI_AP_STATE; WIFI_ADHOC_STATE;
		 * WIFI_ADHOC_MASTER_STATE
		 */
		_clr_fwstate_(pmlmepriv, WIFI_STATION_STATE | WIFI_AP_STATE |
			      WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE);
		switch (networktype) {
		case Ndis802_11IBSS:
			set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			break;
		case Ndis802_11Infrastructure:
			set_fwstate(pmlmepriv, WIFI_STATION_STATE);
			break;
		case Ndis802_11APMode:
			set_fwstate(pmlmepriv, WIFI_AP_STATE);
			break;
		case Ndis802_11AutoUnknown:
		case Ndis802_11InfrastructureMax:
			break;
		}
		spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	}
}