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
struct TYPE_4__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev_addr; } ;
struct team_port {int index; TYPE_2__ orig; int /*<<< orphan*/  list; int /*<<< orphan*/  qom_list; struct team* team; struct net_device* dev; } ;
struct team {int /*<<< orphan*/  port_list; TYPE_1__* mode; struct net_device* dev; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {char* name; int flags; int features; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct TYPE_3__ {scalar_t__ port_priv_size; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_ALLMULTI ; 
 int IFF_LOOPBACK ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NETIF_F_LRO ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  __team_compute_features (struct team*) ; 
 int __team_option_inst_add_port (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  __team_option_inst_del_port (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  __team_options_change_check (struct team*) ; 
 int /*<<< orphan*/  __team_port_change_port_added (struct team_port*,int) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_disable_lro (struct net_device*) ; 
 int /*<<< orphan*/  dev_mc_sync_multiple (struct net_device*,struct net_device*) ; 
 int dev_open (struct net_device*,struct netlink_ext_ack*) ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_uc_sync_multiple (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct team_port*) ; 
 struct team_port* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 scalar_t__ netdev_has_upper_dev (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct team_port*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 
 scalar_t__ netif_is_team_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_oper_up (struct net_device*) ; 
 int team_dev_type_check_change (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  team_handle_frame ; 
 int /*<<< orphan*/  team_port_disable_netpoll (struct team_port*) ; 
 int /*<<< orphan*/  team_port_enable (struct team*,struct team_port*) ; 
 int team_port_enable_netpoll (struct team_port*) ; 
 int team_port_enter (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  team_port_leave (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  team_port_set_orig_dev_addr (struct team_port*) ; 
 int team_upper_dev_link (struct team*,struct team_port*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  team_upper_dev_unlink (struct team*,struct team_port*) ; 
 scalar_t__ vlan_uses_dev (struct net_device*) ; 
 int vlan_vids_add_by_dev (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  vlan_vids_del_by_dev (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int team_port_add(struct team *team, struct net_device *port_dev,
			 struct netlink_ext_ack *extack)
{
	struct net_device *dev = team->dev;
	struct team_port *port;
	char *portname = port_dev->name;
	int err;

	if (port_dev->flags & IFF_LOOPBACK) {
		NL_SET_ERR_MSG(extack, "Loopback device can't be added as a team port");
		netdev_err(dev, "Device %s is loopback device. Loopback devices can't be added as a team port\n",
			   portname);
		return -EINVAL;
	}

	if (netif_is_team_port(port_dev)) {
		NL_SET_ERR_MSG(extack, "Device is already a port of a team device");
		netdev_err(dev, "Device %s is already a port "
				"of a team device\n", portname);
		return -EBUSY;
	}

	if (dev == port_dev) {
		NL_SET_ERR_MSG(extack, "Cannot enslave team device to itself");
		netdev_err(dev, "Cannot enslave team device to itself\n");
		return -EINVAL;
	}

	if (netdev_has_upper_dev(dev, port_dev)) {
		NL_SET_ERR_MSG(extack, "Device is already an upper device of the team interface");
		netdev_err(dev, "Device %s is already an upper device of the team interface\n",
			   portname);
		return -EBUSY;
	}

	if (port_dev->features & NETIF_F_VLAN_CHALLENGED &&
	    vlan_uses_dev(dev)) {
		NL_SET_ERR_MSG(extack, "Device is VLAN challenged and team device has VLAN set up");
		netdev_err(dev, "Device %s is VLAN challenged and team device has VLAN set up\n",
			   portname);
		return -EPERM;
	}

	err = team_dev_type_check_change(dev, port_dev);
	if (err)
		return err;

	if (port_dev->flags & IFF_UP) {
		NL_SET_ERR_MSG(extack, "Device is up. Set it down before adding it as a team port");
		netdev_err(dev, "Device %s is up. Set it down before adding it as a team port\n",
			   portname);
		return -EBUSY;
	}

	port = kzalloc(sizeof(struct team_port) + team->mode->port_priv_size,
		       GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	port->dev = port_dev;
	port->team = team;
	INIT_LIST_HEAD(&port->qom_list);

	port->orig.mtu = port_dev->mtu;
	err = dev_set_mtu(port_dev, dev->mtu);
	if (err) {
		netdev_dbg(dev, "Error %d calling dev_set_mtu\n", err);
		goto err_set_mtu;
	}

	memcpy(port->orig.dev_addr, port_dev->dev_addr, port_dev->addr_len);

	err = team_port_enter(team, port);
	if (err) {
		netdev_err(dev, "Device %s failed to enter team mode\n",
			   portname);
		goto err_port_enter;
	}

	err = dev_open(port_dev, extack);
	if (err) {
		netdev_dbg(dev, "Device %s opening failed\n",
			   portname);
		goto err_dev_open;
	}

	err = vlan_vids_add_by_dev(port_dev, dev);
	if (err) {
		netdev_err(dev, "Failed to add vlan ids to device %s\n",
				portname);
		goto err_vids_add;
	}

	err = team_port_enable_netpoll(port);
	if (err) {
		netdev_err(dev, "Failed to enable netpoll on device %s\n",
			   portname);
		goto err_enable_netpoll;
	}

	if (!(dev->features & NETIF_F_LRO))
		dev_disable_lro(port_dev);

	err = netdev_rx_handler_register(port_dev, team_handle_frame,
					 port);
	if (err) {
		netdev_err(dev, "Device %s failed to register rx_handler\n",
			   portname);
		goto err_handler_register;
	}

	err = team_upper_dev_link(team, port, extack);
	if (err) {
		netdev_err(dev, "Device %s failed to set upper link\n",
			   portname);
		goto err_set_upper_link;
	}

	err = __team_option_inst_add_port(team, port);
	if (err) {
		netdev_err(dev, "Device %s failed to add per-port options\n",
			   portname);
		goto err_option_port_add;
	}

	/* set promiscuity level to new slave */
	if (dev->flags & IFF_PROMISC) {
		err = dev_set_promiscuity(port_dev, 1);
		if (err)
			goto err_set_slave_promisc;
	}

	/* set allmulti level to new slave */
	if (dev->flags & IFF_ALLMULTI) {
		err = dev_set_allmulti(port_dev, 1);
		if (err) {
			if (dev->flags & IFF_PROMISC)
				dev_set_promiscuity(port_dev, -1);
			goto err_set_slave_promisc;
		}
	}

	netif_addr_lock_bh(dev);
	dev_uc_sync_multiple(port_dev, dev);
	dev_mc_sync_multiple(port_dev, dev);
	netif_addr_unlock_bh(dev);

	port->index = -1;
	list_add_tail_rcu(&port->list, &team->port_list);
	team_port_enable(team, port);
	__team_compute_features(team);
	__team_port_change_port_added(port, !!netif_oper_up(port_dev));
	__team_options_change_check(team);

	netdev_info(dev, "Port device %s added\n", portname);

	return 0;

err_set_slave_promisc:
	__team_option_inst_del_port(team, port);

err_option_port_add:
	team_upper_dev_unlink(team, port);

err_set_upper_link:
	netdev_rx_handler_unregister(port_dev);

err_handler_register:
	team_port_disable_netpoll(port);

err_enable_netpoll:
	vlan_vids_del_by_dev(port_dev, dev);

err_vids_add:
	dev_close(port_dev);

err_dev_open:
	team_port_leave(team, port);
	team_port_set_orig_dev_addr(port);

err_port_enter:
	dev_set_mtu(port_dev, port->orig.mtu);

err_set_mtu:
	kfree(port);

	return err;
}