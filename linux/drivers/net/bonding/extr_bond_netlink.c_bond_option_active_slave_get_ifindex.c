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
struct net_device {int ifindex; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 struct net_device* bond_option_active_slave_get_rcu (struct bonding*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int bond_option_active_slave_get_ifindex(struct bonding *bond)
{
	const struct net_device *slave;
	int ifindex;

	rcu_read_lock();
	slave = bond_option_active_slave_get_rcu(bond);
	ifindex = slave ? slave->ifindex : 0;
	rcu_read_unlock();
	return ifindex;
}