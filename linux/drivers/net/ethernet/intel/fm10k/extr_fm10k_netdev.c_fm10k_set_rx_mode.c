#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_xcast_mode ) (struct fm10k_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {int xcast_mode; int /*<<< orphan*/  glort; struct fm10k_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_VLAN_ALL ; 
 int FM10K_XCAST_MODE_ALLMULTI ; 
 int FM10K_XCAST_MODE_MULTI ; 
 int FM10K_XCAST_MODE_NONE ; 
 int FM10K_XCAST_MODE_PROMISC ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_clear_unused_vlans (struct fm10k_intfc*) ; 
 scalar_t__ fm10k_host_mbx_ready (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mc_sync ; 
 int /*<<< orphan*/  fm10k_mc_unsync ; 
 int /*<<< orphan*/  fm10k_queue_vlan_request (struct fm10k_intfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_uc_sync ; 
 int /*<<< orphan*/  fm10k_uc_unsync ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fm10k_set_rx_mode(struct net_device *dev)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_hw *hw = &interface->hw;
	int xcast_mode;

	/* no need to update the harwdare if we are not running */
	if (!(dev->flags & IFF_UP))
		return;

	/* determine new mode based on flags */
	xcast_mode = (dev->flags & IFF_PROMISC) ? FM10K_XCAST_MODE_PROMISC :
		     (dev->flags & IFF_ALLMULTI) ? FM10K_XCAST_MODE_ALLMULTI :
		     (dev->flags & (IFF_BROADCAST | IFF_MULTICAST)) ?
		     FM10K_XCAST_MODE_MULTI : FM10K_XCAST_MODE_NONE;

	fm10k_mbx_lock(interface);

	/* update xcast mode first, but only if it changed */
	if (interface->xcast_mode != xcast_mode) {
		/* update VLAN table when entering promiscuous mode */
		if (xcast_mode == FM10K_XCAST_MODE_PROMISC)
			fm10k_queue_vlan_request(interface, FM10K_VLAN_ALL,
						 0, true);

		/* clear VLAN table when exiting promiscuous mode */
		if (interface->xcast_mode == FM10K_XCAST_MODE_PROMISC)
			fm10k_clear_unused_vlans(interface);

		/* update xcast mode if host's mailbox is ready */
		if (fm10k_host_mbx_ready(interface))
			hw->mac.ops.update_xcast_mode(hw, interface->glort,
						      xcast_mode);

		/* record updated xcast mode state */
		interface->xcast_mode = xcast_mode;
	}

	/* synchronize all of the addresses */
	__dev_uc_sync(dev, fm10k_uc_sync, fm10k_uc_unsync);
	__dev_mc_sync(dev, fm10k_mc_sync, fm10k_mc_unsync);

	fm10k_mbx_unlock(interface);
}