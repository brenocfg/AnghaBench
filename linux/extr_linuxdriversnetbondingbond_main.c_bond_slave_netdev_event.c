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
struct slave {struct bonding* bond; int /*<<< orphan*/  link; } ;
struct net_device {char* name; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/ * primary; } ;
struct bonding {struct net_device* dev; int /*<<< orphan*/  primary_slave; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  BOND_LINK_FAIL ; 
 int /*<<< orphan*/  BOND_MODE (struct bonding*) ; 
 int /*<<< orphan*/  BOND_MODE_8023AD ; 
#define  NETDEV_CHANGE 135 
#define  NETDEV_CHANGEMTU 134 
#define  NETDEV_CHANGENAME 133 
#define  NETDEV_DOWN 132 
#define  NETDEV_FEAT_CHANGE 131 
#define  NETDEV_RESEND_IGMP 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __bond_release_one (struct net_device*,struct net_device*,int,int) ; 
 int /*<<< orphan*/  block_netpoll_tx () ; 
 int /*<<< orphan*/  bond_3ad_adapter_speed_duplex_changed (struct slave*) ; 
 int /*<<< orphan*/  bond_compute_features (struct bonding*) ; 
 int /*<<< orphan*/  bond_mode_can_use_xmit_hash (struct bonding*) ; 
 int /*<<< orphan*/  bond_release_and_destroy (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  bond_select_active_slave (struct bonding*) ; 
 struct slave* bond_slave_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  bond_update_slave_arr (struct bonding*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bond_update_speed_duplex (struct slave*) ; 
 int /*<<< orphan*/  bond_uses_primary (struct bonding*) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (unsigned long,struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct slave*) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unblock_netpoll_tx () ; 

__attribute__((used)) static int bond_slave_netdev_event(unsigned long event,
				   struct net_device *slave_dev)
{
	struct slave *slave = bond_slave_get_rtnl(slave_dev), *primary;
	struct bonding *bond;
	struct net_device *bond_dev;

	/* A netdev event can be generated while enslaving a device
	 * before netdev_rx_handler_register is called in which case
	 * slave will be NULL
	 */
	if (!slave)
		return NOTIFY_DONE;
	bond_dev = slave->bond->dev;
	bond = slave->bond;
	primary = rtnl_dereference(bond->primary_slave);

	switch (event) {
	case NETDEV_UNREGISTER:
		if (bond_dev->type != ARPHRD_ETHER)
			bond_release_and_destroy(bond_dev, slave_dev);
		else
			__bond_release_one(bond_dev, slave_dev, false, true);
		break;
	case NETDEV_UP:
	case NETDEV_CHANGE:
		/* For 802.3ad mode only:
		 * Getting invalid Speed/Duplex values here will put slave
		 * in weird state. So mark it as link-fail for the time
		 * being and let link-monitoring (miimon) set it right when
		 * correct speeds/duplex are available.
		 */
		if (bond_update_speed_duplex(slave) &&
		    BOND_MODE(bond) == BOND_MODE_8023AD)
			slave->link = BOND_LINK_FAIL;

		if (BOND_MODE(bond) == BOND_MODE_8023AD)
			bond_3ad_adapter_speed_duplex_changed(slave);
		/* Fallthrough */
	case NETDEV_DOWN:
		/* Refresh slave-array if applicable!
		 * If the setup does not use miimon or arpmon (mode-specific!),
		 * then these events will not cause the slave-array to be
		 * refreshed. This will cause xmit to use a slave that is not
		 * usable. Avoid such situation by refeshing the array at these
		 * events. If these (miimon/arpmon) parameters are configured
		 * then array gets refreshed twice and that should be fine!
		 */
		if (bond_mode_can_use_xmit_hash(bond))
			bond_update_slave_arr(bond, NULL);
		break;
	case NETDEV_CHANGEMTU:
		/* TODO: Should slaves be allowed to
		 * independently alter their MTU?  For
		 * an active-backup bond, slaves need
		 * not be the same type of device, so
		 * MTUs may vary.  For other modes,
		 * slaves arguably should have the
		 * same MTUs. To do this, we'd need to
		 * take over the slave's change_mtu
		 * function for the duration of their
		 * servitude.
		 */
		break;
	case NETDEV_CHANGENAME:
		/* we don't care if we don't have primary set */
		if (!bond_uses_primary(bond) ||
		    !bond->params.primary[0])
			break;

		if (slave == primary) {
			/* slave's name changed - he's no longer primary */
			RCU_INIT_POINTER(bond->primary_slave, NULL);
		} else if (!strcmp(slave_dev->name, bond->params.primary)) {
			/* we have a new primary slave */
			rcu_assign_pointer(bond->primary_slave, slave);
		} else { /* we didn't change primary - exit */
			break;
		}

		netdev_info(bond->dev, "Primary slave changed to %s, reselecting active slave\n",
			    primary ? slave_dev->name : "none");

		block_netpoll_tx();
		bond_select_active_slave(bond);
		unblock_netpoll_tx();
		break;
	case NETDEV_FEAT_CHANGE:
		bond_compute_features(bond);
		break;
	case NETDEV_RESEND_IGMP:
		/* Propagate to master device */
		call_netdevice_notifiers(event, slave->bond->dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}