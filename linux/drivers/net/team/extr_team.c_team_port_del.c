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
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;
struct team_port {TYPE_1__ orig; int /*<<< orphan*/  list; } ;
struct team {struct net_device* dev; } ;
struct net_device {char* name; int flags; } ;

/* Variables and functions */
 int ENOENT ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  __team_compute_features (struct team*) ; 
 int /*<<< orphan*/  __team_option_inst_del_port (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  __team_option_inst_mark_removed_port (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  __team_options_change_check (struct team*) ; 
 int /*<<< orphan*/  __team_port_change_port_removed (struct team_port*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_mc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_uc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct team_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  team_port_disable (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  team_port_disable_netpoll (struct team_port*) ; 
 int /*<<< orphan*/  team_port_find (struct team*,struct team_port*) ; 
 struct team_port* team_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  team_port_leave (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  team_port_set_orig_dev_addr (struct team_port*) ; 
 int /*<<< orphan*/  team_upper_dev_unlink (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  vlan_vids_del_by_dev (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int team_port_del(struct team *team, struct net_device *port_dev)
{
	struct net_device *dev = team->dev;
	struct team_port *port;
	char *portname = port_dev->name;

	port = team_port_get_rtnl(port_dev);
	if (!port || !team_port_find(team, port)) {
		netdev_err(dev, "Device %s does not act as a port of this team\n",
			   portname);
		return -ENOENT;
	}

	team_port_disable(team, port);
	list_del_rcu(&port->list);

	if (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(port_dev, -1);
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(port_dev, -1);

	team_upper_dev_unlink(team, port);
	netdev_rx_handler_unregister(port_dev);
	team_port_disable_netpoll(port);
	vlan_vids_del_by_dev(port_dev, dev);
	dev_uc_unsync(port_dev, dev);
	dev_mc_unsync(port_dev, dev);
	dev_close(port_dev);
	team_port_leave(team, port);

	__team_option_inst_mark_removed_port(team, port);
	__team_options_change_check(team);
	__team_option_inst_del_port(team, port);
	__team_port_change_port_removed(port);

	team_port_set_orig_dev_addr(port);
	dev_set_mtu(port_dev, port->orig.mtu);
	kfree_rcu(port, rcu);
	netdev_info(dev, "Port device %s removed\n", portname);
	__team_compute_features(team);

	return 0;
}