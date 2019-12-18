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
struct ixgbe_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_macvlan_up ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_configure_dfwd(struct ixgbe_adapter *adapter)
{
	netdev_walk_all_upper_dev_rcu(adapter->netdev,
				      ixgbe_macvlan_up, adapter);
}