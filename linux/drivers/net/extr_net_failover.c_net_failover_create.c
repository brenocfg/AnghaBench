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
struct net_failover_info {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct net_device {int priv_flags; int features; int hw_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; TYPE_1__ dev; } ;
struct failover {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct failover* ERR_PTR (int) ; 
 int FAILOVER_VLAN_FEATURES ; 
 int IFF_NO_QUEUE ; 
 int IFF_TX_SKB_SHARING ; 
 int IFF_UNICAST_FLT ; 
 int IFF_XMIT_DST_RELEASE ; 
 scalar_t__ IS_ERR (struct failover*) ; 
 int NETIF_F_GSO_ENCAP_ALL ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_NETNS_LOCAL ; 
 int PTR_ERR (struct failover*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 struct net_device* alloc_etherdev_mq (int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failover_dev_ops ; 
 int /*<<< orphan*/  failover_ethtool_ops ; 
 struct failover* failover_register (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_failover_ops ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

struct failover *net_failover_create(struct net_device *standby_dev)
{
	struct device *dev = standby_dev->dev.parent;
	struct net_device *failover_dev;
	struct failover *failover;
	int err;

	/* Alloc at least 2 queues, for now we are going with 16 assuming
	 * that VF devices being enslaved won't have too many queues.
	 */
	failover_dev = alloc_etherdev_mq(sizeof(struct net_failover_info), 16);
	if (!failover_dev) {
		dev_err(dev, "Unable to allocate failover_netdev!\n");
		return ERR_PTR(-ENOMEM);
	}

	dev_net_set(failover_dev, dev_net(standby_dev));
	SET_NETDEV_DEV(failover_dev, dev);

	failover_dev->netdev_ops = &failover_dev_ops;
	failover_dev->ethtool_ops = &failover_ethtool_ops;

	/* Initialize the device options */
	failover_dev->priv_flags |= IFF_UNICAST_FLT | IFF_NO_QUEUE;
	failover_dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE |
				       IFF_TX_SKB_SHARING);

	/* don't acquire failover netdev's netif_tx_lock when transmitting */
	failover_dev->features |= NETIF_F_LLTX;

	/* Don't allow failover devices to change network namespaces. */
	failover_dev->features |= NETIF_F_NETNS_LOCAL;

	failover_dev->hw_features = FAILOVER_VLAN_FEATURES |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_HW_VLAN_CTAG_RX |
				    NETIF_F_HW_VLAN_CTAG_FILTER;

	failover_dev->hw_features |= NETIF_F_GSO_ENCAP_ALL;
	failover_dev->features |= failover_dev->hw_features;

	memcpy(failover_dev->dev_addr, standby_dev->dev_addr,
	       failover_dev->addr_len);

	failover_dev->min_mtu = standby_dev->min_mtu;
	failover_dev->max_mtu = standby_dev->max_mtu;

	err = register_netdev(failover_dev);
	if (err) {
		dev_err(dev, "Unable to register failover_dev!\n");
		goto err_register_netdev;
	}

	netif_carrier_off(failover_dev);

	failover = failover_register(failover_dev, &net_failover_ops);
	if (IS_ERR(failover)) {
		err = PTR_ERR(failover);
		goto err_failover_register;
	}

	return failover;

err_failover_register:
	unregister_netdev(failover_dev);
err_register_netdev:
	free_netdev(failover_dev);

	return ERR_PTR(err);
}