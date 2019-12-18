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
struct slave {scalar_t__ link; int /*<<< orphan*/  dev; } ;
struct netdev_lag_lower_state_info {int link_up; int /*<<< orphan*/  tx_enabled; } ;

/* Variables and functions */
 scalar_t__ BOND_LINK_FAIL ; 
 scalar_t__ BOND_LINK_UP ; 
 int /*<<< orphan*/  bond_is_active_slave (struct slave*) ; 
 int /*<<< orphan*/  netdev_lower_state_changed (int /*<<< orphan*/ ,struct netdev_lag_lower_state_info*) ; 

void bond_lower_state_changed(struct slave *slave)
{
	struct netdev_lag_lower_state_info info;

	info.link_up = slave->link == BOND_LINK_UP ||
		       slave->link == BOND_LINK_FAIL;
	info.tx_enabled = bond_is_active_slave(slave);
	netdev_lower_state_changed(slave->dev, &info);
}