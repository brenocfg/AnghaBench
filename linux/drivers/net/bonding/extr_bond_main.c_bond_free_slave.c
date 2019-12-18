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
struct slave {int /*<<< orphan*/  notify_work; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 scalar_t__ BOND_MODE (struct bonding*) ; 
 scalar_t__ BOND_MODE_8023AD ; 
 struct slave* SLAVE_AD_INFO (struct slave*) ; 
 struct bonding* bond_get_bond_by_slave (struct slave*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct slave*) ; 

__attribute__((used)) static void bond_free_slave(struct slave *slave)
{
	struct bonding *bond = bond_get_bond_by_slave(slave);

	cancel_delayed_work_sync(&slave->notify_work);
	if (BOND_MODE(bond) == BOND_MODE_8023AD)
		kfree(SLAVE_AD_INFO(slave));

	kfree(slave);
}