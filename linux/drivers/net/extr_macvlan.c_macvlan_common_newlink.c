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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {scalar_t__ mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; } ;
struct net {int dummy; } ;
struct macvlan_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  vlans; scalar_t__ count; } ;
struct macvlan_dev {scalar_t__ mode; int /*<<< orphan*/  list; int /*<<< orphan*/  flags; int /*<<< orphan*/  set_features; struct macvlan_port* port; struct net_device* dev; struct net_device* lowerdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  IFF_MACVLAN ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_LINK ; 
 size_t IFLA_MACVLAN_FLAGS ; 
 size_t IFLA_MACVLAN_MACADDR_MODE ; 
 size_t IFLA_MACVLAN_MODE ; 
 size_t IFLA_MTU ; 
 int /*<<< orphan*/  MACVLAN_FEATURES ; 
 scalar_t__ MACVLAN_MODE_PASSTHRU ; 
 scalar_t__ MACVLAN_MODE_SOURCE ; 
 scalar_t__ MACVLAN_MODE_VEPA ; 
 struct net_device* __dev_get_by_index (struct net*,void*) ; 
 int /*<<< orphan*/  eth_hw_addr_inherit (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  linkwatch_fire_event (struct net_device*) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int macvlan_changelink_sources (struct macvlan_dev*,int,struct nlattr**) ; 
 struct net_device* macvlan_dev_real_dev (struct net_device*) ; 
 scalar_t__ macvlan_passthru (struct macvlan_port*) ; 
 int macvlan_port_create (struct net_device*) ; 
 int /*<<< orphan*/  macvlan_port_destroy (int /*<<< orphan*/ ) ; 
 struct macvlan_port* macvlan_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  macvlan_set_passthru (struct macvlan_port*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int netdev_upper_dev_link (struct net_device*,struct net_device*,struct netlink_ext_ack*) ; 
 scalar_t__ netif_is_macvlan (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_macvlan_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

int macvlan_common_newlink(struct net *src_net, struct net_device *dev,
			   struct nlattr *tb[], struct nlattr *data[],
			   struct netlink_ext_ack *extack)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvlan_port *port;
	struct net_device *lowerdev;
	int err;
	int macmode;
	bool create = false;

	if (!tb[IFLA_LINK])
		return -EINVAL;

	lowerdev = __dev_get_by_index(src_net, nla_get_u32(tb[IFLA_LINK]));
	if (lowerdev == NULL)
		return -ENODEV;

	/* When creating macvlans or macvtaps on top of other macvlans - use
	 * the real device as the lowerdev.
	 */
	if (netif_is_macvlan(lowerdev))
		lowerdev = macvlan_dev_real_dev(lowerdev);

	if (!tb[IFLA_MTU])
		dev->mtu = lowerdev->mtu;
	else if (dev->mtu > lowerdev->mtu)
		return -EINVAL;

	/* MTU range: 68 - lowerdev->max_mtu */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = lowerdev->max_mtu;

	if (!tb[IFLA_ADDRESS])
		eth_hw_addr_random(dev);

	if (!netif_is_macvlan_port(lowerdev)) {
		err = macvlan_port_create(lowerdev);
		if (err < 0)
			return err;
		create = true;
	}
	port = macvlan_port_get_rtnl(lowerdev);

	/* Only 1 macvlan device can be created in passthru mode */
	if (macvlan_passthru(port)) {
		/* The macvlan port must be not created this time,
		 * still goto destroy_macvlan_port for readability.
		 */
		err = -EINVAL;
		goto destroy_macvlan_port;
	}

	vlan->lowerdev = lowerdev;
	vlan->dev      = dev;
	vlan->port     = port;
	vlan->set_features = MACVLAN_FEATURES;

	vlan->mode     = MACVLAN_MODE_VEPA;
	if (data && data[IFLA_MACVLAN_MODE])
		vlan->mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);

	if (data && data[IFLA_MACVLAN_FLAGS])
		vlan->flags = nla_get_u16(data[IFLA_MACVLAN_FLAGS]);

	if (vlan->mode == MACVLAN_MODE_PASSTHRU) {
		if (port->count) {
			err = -EINVAL;
			goto destroy_macvlan_port;
		}
		macvlan_set_passthru(port);
		eth_hw_addr_inherit(dev, lowerdev);
	}

	if (data && data[IFLA_MACVLAN_MACADDR_MODE]) {
		if (vlan->mode != MACVLAN_MODE_SOURCE) {
			err = -EINVAL;
			goto destroy_macvlan_port;
		}
		macmode = nla_get_u32(data[IFLA_MACVLAN_MACADDR_MODE]);
		err = macvlan_changelink_sources(vlan, macmode, data);
		if (err)
			goto destroy_macvlan_port;
	}

	err = register_netdevice(dev);
	if (err < 0)
		goto destroy_macvlan_port;

	dev->priv_flags |= IFF_MACVLAN;
	err = netdev_upper_dev_link(lowerdev, dev, extack);
	if (err)
		goto unregister_netdev;

	list_add_tail_rcu(&vlan->list, &port->vlans);
	netif_stacked_transfer_operstate(lowerdev, dev);
	linkwatch_fire_event(dev);

	return 0;

unregister_netdev:
	/* macvlan_uninit would free the macvlan port */
	unregister_netdevice(dev);
	return err;
destroy_macvlan_port:
	/* the macvlan port may be freed by macvlan_uninit when fail to register.
	 * so we destroy the macvlan port only when it's valid.
	 */
	if (create && macvlan_port_get_rtnl(lowerdev))
		macvlan_port_destroy(port->dev);
	return err;
}