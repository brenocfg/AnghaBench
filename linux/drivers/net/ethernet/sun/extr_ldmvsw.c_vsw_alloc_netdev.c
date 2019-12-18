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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct vnet_port {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int needed_tailroom; int hw_features; int features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; int /*<<< orphan*/ * dev_addr; int /*<<< orphan*/ * perm_addr; scalar_t__ needed_headroom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VNET_MAX_MTU ; 
 int /*<<< orphan*/  VNET_MAX_TXQS ; 
 scalar_t__ VNET_PACKET_SKIP ; 
 int /*<<< orphan*/  VSW_TX_TIMEOUT ; 
 struct net_device* alloc_etherdev_mqs (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  vsw_ethtool_ops ; 
 int /*<<< orphan*/  vsw_ops ; 

__attribute__((used)) static struct net_device *vsw_alloc_netdev(u8 hwaddr[],
					   struct vio_dev *vdev,
					   u64 handle,
					   u64 port_id)
{
	struct net_device *dev;
	struct vnet_port *port;
	int i;

	dev = alloc_etherdev_mqs(sizeof(*port), VNET_MAX_TXQS, 1);
	if (!dev)
		return ERR_PTR(-ENOMEM);
	dev->needed_headroom = VNET_PACKET_SKIP + 8;
	dev->needed_tailroom = 8;

	for (i = 0; i < ETH_ALEN; i++) {
		dev->dev_addr[i] = hwaddr[i];
		dev->perm_addr[i] = dev->dev_addr[i];
	}

	sprintf(dev->name, "vif%d.%d", (int)handle, (int)port_id);

	dev->netdev_ops = &vsw_ops;
	dev->ethtool_ops = &vsw_ethtool_ops;
	dev->watchdog_timeo = VSW_TX_TIMEOUT;

	dev->hw_features = NETIF_F_HW_CSUM | NETIF_F_SG;
	dev->features = dev->hw_features;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = VNET_MAX_MTU;

	SET_NETDEV_DEV(dev, &vdev->dev);

	return dev;
}