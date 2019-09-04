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
struct TYPE_3__ {scalar_t__ arp_validate; int /*<<< orphan*/ * arp_targets; scalar_t__ miimon; scalar_t__ arp_interval; } ;
struct bonding {int /*<<< orphan*/  arp_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  mii_work; int /*<<< orphan*/ * recv_probe; TYPE_1__ params; TYPE_2__* dev; } ;
struct bond_opt_value {scalar_t__ value; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/ * bond_arp_rcv ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bond_option_arp_interval_set(struct bonding *bond,
					const struct bond_opt_value *newval)
{
	netdev_dbg(bond->dev, "Setting ARP monitoring interval to %llu\n",
		   newval->value);
	bond->params.arp_interval = newval->value;
	if (newval->value) {
		if (bond->params.miimon) {
			netdev_dbg(bond->dev, "ARP monitoring cannot be used with MII monitoring. Disabling MII monitoring\n");
			bond->params.miimon = 0;
		}
		if (!bond->params.arp_targets[0])
			netdev_dbg(bond->dev, "ARP monitoring has been set up, but no ARP targets have been specified\n");
	}
	if (bond->dev->flags & IFF_UP) {
		/* If the interface is up, we may need to fire off
		 * the ARP timer.  If the interface is down, the
		 * timer will get fired off when the open function
		 * is called.
		 */
		if (!newval->value) {
			if (bond->params.arp_validate)
				bond->recv_probe = NULL;
			cancel_delayed_work_sync(&bond->arp_work);
		} else {
			/* arp_validate can be set only in active-backup mode */
			bond->recv_probe = bond_arp_rcv;
			cancel_delayed_work_sync(&bond->mii_work);
			queue_delayed_work(bond->wq, &bond->arp_work, 0);
		}
	}

	return 0;
}