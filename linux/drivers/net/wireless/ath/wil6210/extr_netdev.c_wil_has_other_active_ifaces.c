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
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {struct wil6210_vif** vifs; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int IFF_UP ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 

bool wil_has_other_active_ifaces(struct wil6210_priv *wil,
				 struct net_device *ndev, bool up, bool ok)
{
	int i;
	struct wil6210_vif *vif;
	struct net_device *ndev_i;

	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		vif = wil->vifs[i];
		if (vif) {
			ndev_i = vif_to_ndev(vif);
			if (ndev_i != ndev)
				if ((up && (ndev_i->flags & IFF_UP)) ||
				    (ok && netif_carrier_ok(ndev_i)))
					return true;
		}
	}

	return false;
}