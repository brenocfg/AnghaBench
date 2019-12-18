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
struct net_device {int features; } ;
struct TYPE_2__ {scalar_t__ loopback_mode; } ;
struct bnx2x {scalar_t__ recovery_state; TYPE_1__ link_params; int /*<<< orphan*/  pdev; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ BNX2X_RECOVERY_DONE ; 
 scalar_t__ LOOPBACK_BMAC ; 
 scalar_t__ LOOPBACK_NONE ; 
 int NETIF_F_GRO ; 
 int NETIF_F_LOOPBACK ; 
 int bnx2x_reload_if_running (struct net_device*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_num_vf (int /*<<< orphan*/ ) ; 

int bnx2x_set_features(struct net_device *dev, netdev_features_t features)
{
	struct bnx2x *bp = netdev_priv(dev);
	netdev_features_t changes = features ^ dev->features;
	bool bnx2x_reload = false;
	int rc;

	/* VFs or non SRIOV PFs should be able to change loopback feature */
	if (!pci_num_vf(bp->pdev)) {
		if (features & NETIF_F_LOOPBACK) {
			if (bp->link_params.loopback_mode != LOOPBACK_BMAC) {
				bp->link_params.loopback_mode = LOOPBACK_BMAC;
				bnx2x_reload = true;
			}
		} else {
			if (bp->link_params.loopback_mode != LOOPBACK_NONE) {
				bp->link_params.loopback_mode = LOOPBACK_NONE;
				bnx2x_reload = true;
			}
		}
	}

	/* Don't care about GRO changes */
	changes &= ~NETIF_F_GRO;

	if (changes)
		bnx2x_reload = true;

	if (bnx2x_reload) {
		if (bp->recovery_state == BNX2X_RECOVERY_DONE) {
			dev->features = features;
			rc = bnx2x_reload_if_running(dev);
			return rc ? rc : 1;
		}
		/* else: bnx2x_nic_load() will be called at end of recovery */
	}

	return 0;
}