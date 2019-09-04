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
struct net_device {int dummy; } ;
struct bonding {int /*<<< orphan*/  send_peer_notif; } ;

/* Variables and functions */
#define  NETDEV_CHANGENAME 131 
#define  NETDEV_NOTIFY_PEERS 130 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  bond_create_proc_entry (struct bonding*) ; 
 int bond_event_changename (struct bonding*) ; 
 int /*<<< orphan*/  bond_remove_proc_entry (struct bonding*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bond_master_netdev_event(unsigned long event,
				    struct net_device *bond_dev)
{
	struct bonding *event_bond = netdev_priv(bond_dev);

	switch (event) {
	case NETDEV_CHANGENAME:
		return bond_event_changename(event_bond);
	case NETDEV_UNREGISTER:
		bond_remove_proc_entry(event_bond);
		break;
	case NETDEV_REGISTER:
		bond_create_proc_entry(event_bond);
		break;
	case NETDEV_NOTIFY_PEERS:
		if (event_bond->send_peer_notif)
			event_bond->send_peer_notif--;
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}