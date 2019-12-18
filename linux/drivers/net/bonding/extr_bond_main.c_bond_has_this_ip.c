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
struct bonding {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ bond_confirm_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bond_upper_dev_walk ; 
 scalar_t__ netdev_walk_all_upper_dev_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool bond_has_this_ip(struct bonding *bond, __be32 ip)
{
	bool ret = false;

	if (ip == bond_confirm_addr(bond->dev, 0, ip))
		return true;

	rcu_read_lock();
	if (netdev_walk_all_upper_dev_rcu(bond->dev, bond_upper_dev_walk, &ip))
		ret = true;
	rcu_read_unlock();

	return ret;
}