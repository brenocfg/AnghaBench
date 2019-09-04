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
struct slave {TYPE_1__* dev; } ;
struct bonding {int /*<<< orphan*/  dev; int /*<<< orphan*/  send_peer_notif; int /*<<< orphan*/  curr_active_slave; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __LINK_STATE_LINKWATCH_PENDING ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 struct slave* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bond_should_notify_peers(struct bonding *bond)
{
	struct slave *slave;

	rcu_read_lock();
	slave = rcu_dereference(bond->curr_active_slave);
	rcu_read_unlock();

	netdev_dbg(bond->dev, "bond_should_notify_peers: slave %s\n",
		   slave ? slave->dev->name : "NULL");

	if (!slave || !bond->send_peer_notif ||
	    !netif_carrier_ok(bond->dev) ||
	    test_bit(__LINK_STATE_LINKWATCH_PENDING, &slave->dev->state))
		return false;

	return true;
}