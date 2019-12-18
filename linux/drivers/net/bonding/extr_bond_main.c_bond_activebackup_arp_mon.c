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
struct TYPE_2__ {scalar_t__ arp_interval; } ;
struct bonding {int /*<<< orphan*/  dev; int /*<<< orphan*/  arp_work; int /*<<< orphan*/  wq; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_NOTIFY_PEERS ; 
 int /*<<< orphan*/  bond_ab_arp_commit (struct bonding*) ; 
 scalar_t__ bond_ab_arp_inspect (struct bonding*) ; 
 int bond_ab_arp_probe (struct bonding*) ; 
 int /*<<< orphan*/  bond_has_slaves (struct bonding*) ; 
 int bond_should_notify_peers (struct bonding*) ; 
 int /*<<< orphan*/  bond_slave_link_notify (struct bonding*) ; 
 int /*<<< orphan*/  bond_slave_state_notify (struct bonding*) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtnl_trylock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void bond_activebackup_arp_mon(struct bonding *bond)
{
	bool should_notify_peers = false;
	bool should_notify_rtnl = false;
	int delta_in_ticks;

	delta_in_ticks = msecs_to_jiffies(bond->params.arp_interval);

	if (!bond_has_slaves(bond))
		goto re_arm;

	rcu_read_lock();

	should_notify_peers = bond_should_notify_peers(bond);

	if (bond_ab_arp_inspect(bond)) {
		rcu_read_unlock();

		/* Race avoidance with bond_close flush of workqueue */
		if (!rtnl_trylock()) {
			delta_in_ticks = 1;
			should_notify_peers = false;
			goto re_arm;
		}

		bond_ab_arp_commit(bond);

		rtnl_unlock();
		rcu_read_lock();
	}

	should_notify_rtnl = bond_ab_arp_probe(bond);
	rcu_read_unlock();

re_arm:
	if (bond->params.arp_interval)
		queue_delayed_work(bond->wq, &bond->arp_work, delta_in_ticks);

	if (should_notify_peers || should_notify_rtnl) {
		if (!rtnl_trylock())
			return;

		if (should_notify_peers)
			call_netdevice_notifiers(NETDEV_NOTIFY_PEERS,
						 bond->dev);
		if (should_notify_rtnl) {
			bond_slave_state_notify(bond);
			bond_slave_link_notify(bond);
		}

		rtnl_unlock();
	}
}