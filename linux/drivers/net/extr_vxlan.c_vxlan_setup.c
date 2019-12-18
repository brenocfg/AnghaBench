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
struct vxlan_dev {int /*<<< orphan*/ * fdb_head; int /*<<< orphan*/ * hash_lock; int /*<<< orphan*/  gro_cells; struct net_device* dev; int /*<<< orphan*/  age_timer; int /*<<< orphan*/  next; } ;
struct net_device {int needs_free_netdev; int features; int vlan_features; int hw_features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 unsigned int FDB_HASH_SIZE ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NETIF_F_GSO_SOFTWARE ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  gro_cells_init (int /*<<< orphan*/ *,struct net_device*) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_cleanup ; 
 int /*<<< orphan*/  vxlan_type ; 

__attribute__((used)) static void vxlan_setup(struct net_device *dev)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	unsigned int h;

	eth_hw_addr_random(dev);
	ether_setup(dev);

	dev->needs_free_netdev = true;
	SET_NETDEV_DEVTYPE(dev, &vxlan_type);

	dev->features	|= NETIF_F_LLTX;
	dev->features	|= NETIF_F_SG | NETIF_F_HW_CSUM;
	dev->features   |= NETIF_F_RXCSUM;
	dev->features   |= NETIF_F_GSO_SOFTWARE;

	dev->vlan_features = dev->features;
	dev->hw_features |= NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_RXCSUM;
	dev->hw_features |= NETIF_F_GSO_SOFTWARE;
	netif_keep_dst(dev);
	dev->priv_flags |= IFF_NO_QUEUE;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = ETH_MAX_MTU;

	INIT_LIST_HEAD(&vxlan->next);

	timer_setup(&vxlan->age_timer, vxlan_cleanup, TIMER_DEFERRABLE);

	vxlan->dev = dev;

	gro_cells_init(&vxlan->gro_cells, dev);

	for (h = 0; h < FDB_HASH_SIZE; ++h) {
		spin_lock_init(&vxlan->hash_lock[h]);
		INIT_HLIST_HEAD(&vxlan->fdb_head[h]);
	}
}