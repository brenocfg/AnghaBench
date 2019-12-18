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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  IB_SPEED_DDR ; 
 int /*<<< orphan*/  IB_SPEED_EDR ; 
 int /*<<< orphan*/  IB_SPEED_FDR10 ; 
 int /*<<< orphan*/  IB_SPEED_SDR ; 
 int /*<<< orphan*/  IB_WIDTH_1X ; 
 int /*<<< orphan*/  IB_WIDTH_4X ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 scalar_t__ SPEED_20000 ; 
 scalar_t__ SPEED_25000 ; 
 scalar_t__ SPEED_40000 ; 
 int __ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* ib_device_get_netdev (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int ib_get_eth_speed(struct ib_device *dev, u8 port_num, u8 *speed, u8 *width)
{
	int rc;
	u32 netdev_speed;
	struct net_device *netdev;
	struct ethtool_link_ksettings lksettings;

	if (rdma_port_get_link_layer(dev, port_num) != IB_LINK_LAYER_ETHERNET)
		return -EINVAL;

	netdev = ib_device_get_netdev(dev, port_num);
	if (!netdev)
		return -ENODEV;

	rtnl_lock();
	rc = __ethtool_get_link_ksettings(netdev, &lksettings);
	rtnl_unlock();

	dev_put(netdev);

	if (!rc) {
		netdev_speed = lksettings.base.speed;
	} else {
		netdev_speed = SPEED_1000;
		pr_warn("%s speed is unknown, defaulting to %d\n", netdev->name,
			netdev_speed);
	}

	if (netdev_speed <= SPEED_1000) {
		*width = IB_WIDTH_1X;
		*speed = IB_SPEED_SDR;
	} else if (netdev_speed <= SPEED_10000) {
		*width = IB_WIDTH_1X;
		*speed = IB_SPEED_FDR10;
	} else if (netdev_speed <= SPEED_20000) {
		*width = IB_WIDTH_4X;
		*speed = IB_SPEED_DDR;
	} else if (netdev_speed <= SPEED_25000) {
		*width = IB_WIDTH_1X;
		*speed = IB_SPEED_EDR;
	} else if (netdev_speed <= SPEED_40000) {
		*width = IB_WIDTH_4X;
		*speed = IB_SPEED_FDR10;
	} else {
		*width = IB_WIDTH_4X;
		*speed = IB_SPEED_EDR;
	}

	return 0;
}