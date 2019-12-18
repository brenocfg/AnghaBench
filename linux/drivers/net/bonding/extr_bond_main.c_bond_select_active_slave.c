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
struct slave {int dummy; } ;
struct bonding {int /*<<< orphan*/  dev; int /*<<< orphan*/  curr_active_slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  bond_change_active_slave (struct bonding*,struct slave*) ; 
 struct slave* bond_find_best_slave (struct bonding*) ; 
 int bond_set_carrier (struct bonding*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 

void bond_select_active_slave(struct bonding *bond)
{
	struct slave *best_slave;
	int rv;

	ASSERT_RTNL();

	best_slave = bond_find_best_slave(bond);
	if (best_slave != rtnl_dereference(bond->curr_active_slave)) {
		bond_change_active_slave(bond, best_slave);
		rv = bond_set_carrier(bond);
		if (!rv)
			return;

		if (netif_carrier_ok(bond->dev))
			netdev_info(bond->dev, "active interface up!\n");
		else
			netdev_info(bond->dev, "now running without any active interface!\n");
	}
}