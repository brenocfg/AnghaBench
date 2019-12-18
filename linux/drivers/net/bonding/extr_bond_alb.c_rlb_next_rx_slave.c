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
struct bonding {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct slave* __rlb_next_rx_slave (struct bonding*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct slave *rlb_next_rx_slave(struct bonding *bond)
{
	struct slave *rx_slave;

	ASSERT_RTNL();

	rcu_read_lock();
	rx_slave = __rlb_next_rx_slave(bond);
	rcu_read_unlock();

	return rx_slave;
}