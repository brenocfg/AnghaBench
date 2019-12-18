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
struct slave {int /*<<< orphan*/  perm_hwaddr; TYPE_1__* dev; } ;
struct bonding {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  alb_fasten_mac_swap (struct bonding*,struct slave*,struct slave*) ; 
 int /*<<< orphan*/  alb_swap_mac_addr (struct slave*,struct slave*) ; 
 struct slave* bond_slave_has_mac (struct bonding*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alb_change_hw_addr_on_detach(struct bonding *bond, struct slave *slave)
{
	int perm_curr_diff;
	int perm_bond_diff;
	struct slave *found_slave;

	perm_curr_diff = !ether_addr_equal_64bits(slave->perm_hwaddr,
						  slave->dev->dev_addr);
	perm_bond_diff = !ether_addr_equal_64bits(slave->perm_hwaddr,
						  bond->dev->dev_addr);

	if (perm_curr_diff && perm_bond_diff) {
		found_slave = bond_slave_has_mac(bond, slave->perm_hwaddr);

		if (found_slave) {
			alb_swap_mac_addr(slave, found_slave);
			alb_fasten_mac_swap(bond, slave, found_slave);
		}
	}
}