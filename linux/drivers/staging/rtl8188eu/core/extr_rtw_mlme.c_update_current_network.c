#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlan_bssid_ex {int dummy; } ;
struct ndis_802_11_fixed_ie {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ie_length; scalar_t__ ies; } ;
struct TYPE_4__ {TYPE_2__ network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_same_network (TYPE_2__*,struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  rtw_update_protection (struct adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_network (TYPE_2__*,struct wlan_bssid_ex*,struct adapter*,int) ; 

__attribute__((used)) static void update_current_network(struct adapter *adapter, struct wlan_bssid_ex *pnetwork)
{
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;

	if (check_fwstate(pmlmepriv, _FW_LINKED) &&
	    is_same_network(&pmlmepriv->cur_network.network, pnetwork)) {
		update_network(&pmlmepriv->cur_network.network, pnetwork, adapter, true);
		rtw_update_protection(adapter, (pmlmepriv->cur_network.network.ies) + sizeof(struct ndis_802_11_fixed_ie),
				      pmlmepriv->cur_network.network.ie_length);
	}
}