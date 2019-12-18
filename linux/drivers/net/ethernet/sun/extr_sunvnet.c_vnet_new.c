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
typedef  int u64 ;
struct vnet {int local_mac; int /*<<< orphan*/  list; int /*<<< orphan*/ * port_hash; int /*<<< orphan*/  port_list; struct net_device* dev; int /*<<< orphan*/  lock; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int needed_tailroom; int* dev_addr; int hw_features; int features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; scalar_t__ needed_headroom; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vnet* ERR_PTR (int) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NETIF_F_ALL_TSO ; 
 int NETIF_F_GSO ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VNET_MAX_MTU ; 
 int /*<<< orphan*/  VNET_MAX_TXQS ; 
 scalar_t__ VNET_PACKET_SKIP ; 
 int VNET_PORT_HASH_SIZE ; 
 int /*<<< orphan*/  VNET_TX_TIMEOUT ; 
 struct net_device* alloc_etherdev_mqs (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int*) ; 
 struct vnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnet_ethtool_ops ; 
 int /*<<< orphan*/  vnet_list ; 
 int /*<<< orphan*/  vnet_ops ; 

__attribute__((used)) static struct vnet *vnet_new(const u64 *local_mac,
			     struct vio_dev *vdev)
{
	struct net_device *dev;
	struct vnet *vp;
	int err, i;

	dev = alloc_etherdev_mqs(sizeof(*vp), VNET_MAX_TXQS, 1);
	if (!dev)
		return ERR_PTR(-ENOMEM);
	dev->needed_headroom = VNET_PACKET_SKIP + 8;
	dev->needed_tailroom = 8;

	for (i = 0; i < ETH_ALEN; i++)
		dev->dev_addr[i] = (*local_mac >> (5 - i) * 8) & 0xff;

	vp = netdev_priv(dev);

	spin_lock_init(&vp->lock);
	vp->dev = dev;

	INIT_LIST_HEAD(&vp->port_list);
	for (i = 0; i < VNET_PORT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&vp->port_hash[i]);
	INIT_LIST_HEAD(&vp->list);
	vp->local_mac = *local_mac;

	dev->netdev_ops = &vnet_ops;
	dev->ethtool_ops = &vnet_ethtool_ops;
	dev->watchdog_timeo = VNET_TX_TIMEOUT;

	dev->hw_features = NETIF_F_TSO | NETIF_F_GSO | NETIF_F_ALL_TSO |
			   NETIF_F_HW_CSUM | NETIF_F_SG;
	dev->features = dev->hw_features;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = VNET_MAX_MTU;

	SET_NETDEV_DEV(dev, &vdev->dev);

	err = register_netdev(dev);
	if (err) {
		pr_err("Cannot register net device, aborting\n");
		goto err_out_free_dev;
	}

	netdev_info(dev, "Sun LDOM vnet %pM\n", dev->dev_addr);

	list_add(&vp->list, &vnet_list);

	return vp;

err_out_free_dev:
	free_netdev(dev);

	return ERR_PTR(err);
}