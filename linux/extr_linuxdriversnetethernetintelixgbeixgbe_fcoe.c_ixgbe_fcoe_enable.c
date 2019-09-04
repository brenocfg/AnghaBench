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
struct net_device {TYPE_1__* netdev_ops; int /*<<< orphan*/  features; } ;
struct ixgbe_fcoe {int /*<<< orphan*/  refcnt; } ;
struct ixgbe_adapter {int flags; struct ixgbe_fcoe fcoe; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int IXGBE_FLAG_FCOE_CAPABLE ; 
 int IXGBE_FLAG_FCOE_ENABLED ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int /*<<< orphan*/  NETIF_F_FCOE_MTU ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixgbe_clear_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_fcoe_ddp_enable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_init_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  netdev_features_change (struct net_device*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

int ixgbe_fcoe_enable(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_fcoe *fcoe = &adapter->fcoe;

	atomic_inc(&fcoe->refcnt);

	if (!(adapter->flags & IXGBE_FLAG_FCOE_CAPABLE))
		return -EINVAL;

	if (adapter->flags & IXGBE_FLAG_FCOE_ENABLED)
		return -EINVAL;

	e_info(drv, "Enabling FCoE offload features.\n");

	if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		e_warn(probe, "Enabling FCoE on PF will disable legacy VFs\n");

	if (netif_running(netdev))
		netdev->netdev_ops->ndo_stop(netdev);

	/* Allocate per CPU memory to track DDP pools */
	ixgbe_fcoe_ddp_enable(adapter);

	/* enable FCoE and notify stack */
	adapter->flags |= IXGBE_FLAG_FCOE_ENABLED;
	netdev->features |= NETIF_F_FCOE_MTU;
	netdev_features_change(netdev);

	/* release existing queues and reallocate them */
	ixgbe_clear_interrupt_scheme(adapter);
	ixgbe_init_interrupt_scheme(adapter);

	if (netif_running(netdev))
		netdev->netdev_ops->ndo_open(netdev);

	return 0;
}