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
typedef  void* u16 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {scalar_t__ type; int flags; int dev_id; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  dev_addr; } ;
struct net {int dummy; } ;
struct ipvl_port {int dev_id_start; int /*<<< orphan*/  ida; int /*<<< orphan*/  ipvlans; void* flags; } ;
struct ipvl_dev {int /*<<< orphan*/  pnode; struct ipvl_port* port; int /*<<< orphan*/  addrs_lock; int /*<<< orphan*/  addrs; int /*<<< orphan*/  sfeatures; struct net_device* dev; struct net_device* phy_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFF_NO_RX_HANDLER ; 
 size_t IFLA_IPVLAN_FLAGS ; 
 size_t IFLA_IPVLAN_MODE ; 
 size_t IFLA_LINK ; 
 size_t IFLA_MTU ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPVLAN_FEATURES ; 
 void* IPVLAN_MODE_L3 ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dev_net (struct net_device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipvlan_adjust_mtu (struct ipvl_dev*,struct net_device*) ; 
 struct ipvl_port* ipvlan_port_get_rtnl (struct net_device*) ; 
 int ipvlan_set_port_mode (struct ipvl_port*,void*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ netdev_is_rx_handler_busy (struct net_device*) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 
 int netdev_upper_dev_link (struct net_device*,struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 scalar_t__ netif_is_ipvlan (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_ipvlan_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 void* nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

int ipvlan_link_new(struct net *src_net, struct net_device *dev,
		    struct nlattr *tb[], struct nlattr *data[],
		    struct netlink_ext_ack *extack)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct ipvl_port *port;
	struct net_device *phy_dev;
	int err;
	u16 mode = IPVLAN_MODE_L3;

	if (!tb[IFLA_LINK])
		return -EINVAL;

	phy_dev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	if (!phy_dev)
		return -ENODEV;

	if (netif_is_ipvlan(phy_dev)) {
		struct ipvl_dev *tmp = netdev_priv(phy_dev);

		phy_dev = tmp->phy_dev;
		if (!ns_capable(dev_net(phy_dev)->user_ns, CAP_NET_ADMIN))
			return -EPERM;
	} else if (!netif_is_ipvlan_port(phy_dev)) {
		/* Exit early if the underlying link is invalid or busy */
		if (phy_dev->type != ARPHRD_ETHER ||
		    phy_dev->flags & IFF_LOOPBACK) {
			netdev_err(phy_dev,
				   "Master is either lo or non-ether device\n");
			return -EINVAL;
		}

		if (netdev_is_rx_handler_busy(phy_dev)) {
			netdev_err(phy_dev, "Device is already in use.\n");
			return -EBUSY;
		}
	}

	ipvlan->phy_dev = phy_dev;
	ipvlan->dev = dev;
	ipvlan->sfeatures = IPVLAN_FEATURES;
	if (!tb[IFLA_MTU])
		ipvlan_adjust_mtu(ipvlan, phy_dev);
	INIT_LIST_HEAD(&ipvlan->addrs);
	spin_lock_init(&ipvlan->addrs_lock);

	/* TODO Probably put random address here to be presented to the
	 * world but keep using the physical-dev address for the outgoing
	 * packets.
	 */
	memcpy(dev->dev_addr, phy_dev->dev_addr, ETH_ALEN);

	dev->priv_flags |= IFF_NO_RX_HANDLER;

	err = register_netdevice(dev);
	if (err < 0)
		return err;

	/* ipvlan_init() would have created the port, if required */
	port = ipvlan_port_get_rtnl(phy_dev);
	ipvlan->port = port;

	/* If the port-id base is at the MAX value, then wrap it around and
	 * begin from 0x1 again. This may be due to a busy system where lots
	 * of slaves are getting created and deleted.
	 */
	if (port->dev_id_start == 0xFFFE)
		port->dev_id_start = 0x1;

	/* Since L2 address is shared among all IPvlan slaves including
	 * master, use unique 16 bit dev-ids to diffentiate among them.
	 * Assign IDs between 0x1 and 0xFFFE (used by the master) to each
	 * slave link [see addrconf_ifid_eui48()].
	 */
	err = ida_simple_get(&port->ida, port->dev_id_start, 0xFFFE,
			     GFP_KERNEL);
	if (err < 0)
		err = ida_simple_get(&port->ida, 0x1, port->dev_id_start,
				     GFP_KERNEL);
	if (err < 0)
		goto unregister_netdev;
	dev->dev_id = err;

	/* Increment id-base to the next slot for the future assignment */
	port->dev_id_start = err + 1;

	err = netdev_upper_dev_link(phy_dev, dev, extack);
	if (err)
		goto remove_ida;

	/* Flags are per port and latest update overrides. User has
	 * to be consistent in setting it just like the mode attribute.
	 */
	if (data && data[IFLA_IPVLAN_FLAGS])
		port->flags = nla_get_u16(data[IFLA_IPVLAN_FLAGS]);

	if (data && data[IFLA_IPVLAN_MODE])
		mode = nla_get_u16(data[IFLA_IPVLAN_MODE]);

	err = ipvlan_set_port_mode(port, mode, extack);
	if (err)
		goto unlink_netdev;

	list_add_tail_rcu(&ipvlan->pnode, &port->ipvlans);
	netif_stacked_transfer_operstate(phy_dev, dev);
	return 0;

unlink_netdev:
	netdev_upper_dev_unlink(phy_dev, dev);
remove_ida:
	ida_simple_remove(&port->ida, dev->dev_id);
unregister_netdev:
	unregister_netdevice(dev);
	return err;
}