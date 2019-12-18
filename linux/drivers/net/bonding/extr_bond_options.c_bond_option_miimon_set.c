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
struct TYPE_3__ {int miimon; int updelay; int downdelay; int peer_notif_delay; scalar_t__ arp_validate; scalar_t__ arp_interval; } ;
struct bonding {int /*<<< orphan*/  mii_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  arp_work; TYPE_2__* dev; TYPE_1__ params; } ;
struct bond_opt_value {int value; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 scalar_t__ BOND_ARP_VALIDATE_NONE ; 
 int IFF_UP ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bond_option_miimon_set(struct bonding *bond,
				  const struct bond_opt_value *newval)
{
	netdev_dbg(bond->dev, "Setting MII monitoring interval to %llu\n",
		   newval->value);
	bond->params.miimon = newval->value;
	if (bond->params.updelay)
		netdev_dbg(bond->dev, "Note: Updating updelay (to %d) since it is a multiple of the miimon value\n",
			   bond->params.updelay * bond->params.miimon);
	if (bond->params.downdelay)
		netdev_dbg(bond->dev, "Note: Updating downdelay (to %d) since it is a multiple of the miimon value\n",
			   bond->params.downdelay * bond->params.miimon);
	if (bond->params.peer_notif_delay)
		netdev_dbg(bond->dev, "Note: Updating peer_notif_delay (to %d) since it is a multiple of the miimon value\n",
			   bond->params.peer_notif_delay * bond->params.miimon);
	if (newval->value && bond->params.arp_interval) {
		netdev_dbg(bond->dev, "MII monitoring cannot be used with ARP monitoring - disabling ARP monitoring...\n");
		bond->params.arp_interval = 0;
		if (bond->params.arp_validate)
			bond->params.arp_validate = BOND_ARP_VALIDATE_NONE;
	}
	if (bond->dev->flags & IFF_UP) {
		/* If the interface is up, we may need to fire off
		 * the MII timer. If the interface is down, the
		 * timer will get fired off when the open function
		 * is called.
		 */
		if (!newval->value) {
			cancel_delayed_work_sync(&bond->mii_work);
		} else {
			cancel_delayed_work_sync(&bond->arp_work);
			queue_delayed_work(bond->wq, &bond->mii_work, 0);
		}
	}

	return 0;
}