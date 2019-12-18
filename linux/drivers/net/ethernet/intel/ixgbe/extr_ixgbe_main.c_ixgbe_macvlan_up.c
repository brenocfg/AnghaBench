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
struct net_device {int dummy; } ;
struct ixgbe_fwd_adapter {int dummy; } ;
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_fwd_ring_up (struct ixgbe_adapter*,struct ixgbe_fwd_adapter*) ; 
 struct ixgbe_fwd_adapter* macvlan_accel_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_macvlan (struct net_device*) ; 

__attribute__((used)) static int ixgbe_macvlan_up(struct net_device *vdev, void *data)
{
	struct ixgbe_adapter *adapter = data;
	struct ixgbe_fwd_adapter *accel;

	if (!netif_is_macvlan(vdev))
		return 0;

	accel = macvlan_accel_priv(vdev);
	if (!accel)
		return 0;

	ixgbe_fwd_ring_up(adapter, accel);

	return 0;
}