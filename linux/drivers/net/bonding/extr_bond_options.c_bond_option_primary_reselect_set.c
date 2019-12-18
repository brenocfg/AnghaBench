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
struct TYPE_2__ {int /*<<< orphan*/  primary_reselect; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct bond_opt_value {int /*<<< orphan*/  value; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_netpoll_tx () ; 
 int /*<<< orphan*/  bond_select_active_slave (struct bonding*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unblock_netpoll_tx () ; 

__attribute__((used)) static int bond_option_primary_reselect_set(struct bonding *bond,
					    const struct bond_opt_value *newval)
{
	netdev_dbg(bond->dev, "Setting primary_reselect to %s (%llu)\n",
		   newval->string, newval->value);
	bond->params.primary_reselect = newval->value;

	block_netpoll_tx();
	bond_select_active_slave(bond);
	unblock_netpoll_tx();

	return 0;
}