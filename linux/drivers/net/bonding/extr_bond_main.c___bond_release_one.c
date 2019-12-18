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
struct sockaddr_storage {int /*<<< orphan*/  ss_family; int /*<<< orphan*/  __data; } ;
struct sockaddr {int dummy; } ;
struct slave {int /*<<< orphan*/  original_mtu; TYPE_2__* dev; int /*<<< orphan*/  perm_hwaddr; } ;
struct net_device {int flags; int features; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {scalar_t__ fail_over_mac; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/  dev; int /*<<< orphan*/  slave_cnt; int /*<<< orphan*/  curr_active_slave; int /*<<< orphan*/  primary_slave; int /*<<< orphan*/  current_arp_slave; int /*<<< orphan*/  bond_stats; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 scalar_t__ BOND_FOM_ACTIVE ; 
 scalar_t__ BOND_MODE (struct bonding*) ; 
 scalar_t__ BOND_MODE_8023AD ; 
 scalar_t__ BOND_MODE_ACTIVEBACKUP ; 
 int /*<<< orphan*/  BOND_SLAVE_NOTIFY_NOW ; 
 int EINVAL ; 
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  IFF_BONDING ; 
 int IFF_PROMISC ; 
 int IFF_SLAVE ; 
 int /*<<< orphan*/  NETDEV_CHANGEADDR ; 
 int /*<<< orphan*/  NETDEV_RELEASE ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_netpoll_tx () ; 
 int /*<<< orphan*/  bond_3ad_unbind_slave (struct slave*) ; 
 int /*<<< orphan*/  bond_alb_deinit_slave (struct bonding*,struct slave*) ; 
 int /*<<< orphan*/  bond_change_active_slave (struct bonding*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bond_compute_features (struct bonding*) ; 
 int /*<<< orphan*/  bond_free_slave (struct slave*) ; 
 struct slave* bond_get_slave_by_dev (struct bonding*,struct net_device*) ; 
 int /*<<< orphan*/  bond_get_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bond_has_slaves (struct bonding*) ; 
 int /*<<< orphan*/  bond_hw_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_hw_addr_flush (struct net_device*,struct net_device*) ; 
 scalar_t__ bond_is_active_slave (struct slave*) ; 
 scalar_t__ bond_is_lb (struct bonding*) ; 
 scalar_t__ bond_mode_can_use_xmit_hash (struct bonding*) ; 
 int /*<<< orphan*/  bond_select_active_slave (struct bonding*) ; 
 int /*<<< orphan*/  bond_set_carrier (struct bonding*) ; 
 int /*<<< orphan*/  bond_set_slave_inactive_flags (struct slave*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bond_sysfs_slave_del (struct slave*) ; 
 int /*<<< orphan*/  bond_update_slave_arr (struct bonding*,struct slave*) ; 
 int /*<<< orphan*/  bond_upper_dev_unlink (struct bonding*,struct slave*) ; 
 int /*<<< orphan*/  bond_uses_primary (struct bonding*) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_mac_address (struct net_device*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_has_upper_dev (struct net_device*,struct net_device*) ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bond_master (struct net_device*) ; 
 struct slave* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_dbg (struct net_device*,struct net_device*,char*) ; 
 int /*<<< orphan*/  slave_disable_netpoll (struct slave*) ; 
 int /*<<< orphan*/  slave_info (struct net_device*,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  slave_warn (struct net_device*,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  unblock_netpoll_tx () ; 
 int /*<<< orphan*/  vlan_vids_del_by_dev (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int __bond_release_one(struct net_device *bond_dev,
			      struct net_device *slave_dev,
			      bool all, bool unregister)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct slave *slave, *oldcurrent;
	struct sockaddr_storage ss;
	int old_flags = bond_dev->flags;
	netdev_features_t old_features = bond_dev->features;

	/* slave is not a slave or master is not master of this slave */
	if (!(slave_dev->flags & IFF_SLAVE) ||
	    !netdev_has_upper_dev(slave_dev, bond_dev)) {
		slave_dbg(bond_dev, slave_dev, "cannot release slave\n");
		return -EINVAL;
	}

	block_netpoll_tx();

	slave = bond_get_slave_by_dev(bond, slave_dev);
	if (!slave) {
		/* not a slave of this bond */
		slave_info(bond_dev, slave_dev, "interface not enslaved\n");
		unblock_netpoll_tx();
		return -EINVAL;
	}

	bond_set_slave_inactive_flags(slave, BOND_SLAVE_NOTIFY_NOW);

	bond_sysfs_slave_del(slave);

	/* recompute stats just before removing the slave */
	bond_get_stats(bond->dev, &bond->bond_stats);

	bond_upper_dev_unlink(bond, slave);
	/* unregister rx_handler early so bond_handle_frame wouldn't be called
	 * for this slave anymore.
	 */
	netdev_rx_handler_unregister(slave_dev);

	if (BOND_MODE(bond) == BOND_MODE_8023AD)
		bond_3ad_unbind_slave(slave);

	if (bond_mode_can_use_xmit_hash(bond))
		bond_update_slave_arr(bond, slave);

	slave_info(bond_dev, slave_dev, "Releasing %s interface\n",
		    bond_is_active_slave(slave) ? "active" : "backup");

	oldcurrent = rcu_access_pointer(bond->curr_active_slave);

	RCU_INIT_POINTER(bond->current_arp_slave, NULL);

	if (!all && (!bond->params.fail_over_mac ||
		     BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP)) {
		if (ether_addr_equal_64bits(bond_dev->dev_addr, slave->perm_hwaddr) &&
		    bond_has_slaves(bond))
			slave_warn(bond_dev, slave_dev, "the permanent HWaddr of slave - %pM - is still in use by bond - set the HWaddr of slave to a different address to avoid conflicts\n",
				   slave->perm_hwaddr);
	}

	if (rtnl_dereference(bond->primary_slave) == slave)
		RCU_INIT_POINTER(bond->primary_slave, NULL);

	if (oldcurrent == slave)
		bond_change_active_slave(bond, NULL);

	if (bond_is_lb(bond)) {
		/* Must be called only after the slave has been
		 * detached from the list and the curr_active_slave
		 * has been cleared (if our_slave == old_current),
		 * but before a new active slave is selected.
		 */
		bond_alb_deinit_slave(bond, slave);
	}

	if (all) {
		RCU_INIT_POINTER(bond->curr_active_slave, NULL);
	} else if (oldcurrent == slave) {
		/* Note that we hold RTNL over this sequence, so there
		 * is no concern that another slave add/remove event
		 * will interfere.
		 */
		bond_select_active_slave(bond);
	}

	if (!bond_has_slaves(bond)) {
		bond_set_carrier(bond);
		eth_hw_addr_random(bond_dev);
	}

	unblock_netpoll_tx();
	synchronize_rcu();
	bond->slave_cnt--;

	if (!bond_has_slaves(bond)) {
		call_netdevice_notifiers(NETDEV_CHANGEADDR, bond->dev);
		call_netdevice_notifiers(NETDEV_RELEASE, bond->dev);
	}

	bond_compute_features(bond);
	if (!(bond_dev->features & NETIF_F_VLAN_CHALLENGED) &&
	    (old_features & NETIF_F_VLAN_CHALLENGED))
		slave_info(bond_dev, slave_dev, "last VLAN challenged slave left bond - VLAN blocking is removed\n");

	vlan_vids_del_by_dev(slave_dev, bond_dev);

	/* If the mode uses primary, then this case was handled above by
	 * bond_change_active_slave(..., NULL)
	 */
	if (!bond_uses_primary(bond)) {
		/* unset promiscuity level from slave
		 * NOTE: The NETDEV_CHANGEADDR call above may change the value
		 * of the IFF_PROMISC flag in the bond_dev, but we need the
		 * value of that flag before that change, as that was the value
		 * when this slave was attached, so we cache at the start of the
		 * function and use it here. Same goes for ALLMULTI below
		 */
		if (old_flags & IFF_PROMISC)
			dev_set_promiscuity(slave_dev, -1);

		/* unset allmulti level from slave */
		if (old_flags & IFF_ALLMULTI)
			dev_set_allmulti(slave_dev, -1);

		bond_hw_addr_flush(bond_dev, slave_dev);
	}

	slave_disable_netpoll(slave);

	/* close slave before restoring its mac address */
	dev_close(slave_dev);

	if (bond->params.fail_over_mac != BOND_FOM_ACTIVE ||
	    BOND_MODE(bond) != BOND_MODE_ACTIVEBACKUP) {
		/* restore original ("permanent") mac address */
		bond_hw_addr_copy(ss.__data, slave->perm_hwaddr,
				  slave->dev->addr_len);
		ss.ss_family = slave_dev->type;
		dev_set_mac_address(slave_dev, (struct sockaddr *)&ss, NULL);
	}

	if (unregister)
		__dev_set_mtu(slave_dev, slave->original_mtu);
	else
		dev_set_mtu(slave_dev, slave->original_mtu);

	if (!netif_is_bond_master(slave_dev))
		slave_dev->priv_flags &= ~IFF_BONDING;

	bond_free_slave(slave);

	return 0;
}