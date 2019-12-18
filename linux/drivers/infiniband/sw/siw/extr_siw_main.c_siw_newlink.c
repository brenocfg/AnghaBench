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
struct siw_device {int /*<<< orphan*/  base_dev; int /*<<< orphan*/  state; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  RDMA_DRIVER_SIW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 struct ib_device* ib_device_get_by_netdev (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  siw_dev_qualified (struct net_device*) ; 
 struct siw_device* siw_device_create (struct net_device*) ; 
 int siw_device_register (struct siw_device*,char const*) ; 

__attribute__((used)) static int siw_newlink(const char *basedev_name, struct net_device *netdev)
{
	struct ib_device *base_dev;
	struct siw_device *sdev = NULL;
	int rv = -ENOMEM;

	if (!siw_dev_qualified(netdev))
		return -EINVAL;

	base_dev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_SIW);
	if (base_dev) {
		ib_device_put(base_dev);
		return -EEXIST;
	}
	sdev = siw_device_create(netdev);
	if (sdev) {
		dev_dbg(&netdev->dev, "siw: new device\n");

		if (netif_running(netdev) && netif_carrier_ok(netdev))
			sdev->state = IB_PORT_ACTIVE;
		else
			sdev->state = IB_PORT_DOWN;

		rv = siw_device_register(sdev, basedev_name);
		if (rv)
			ib_dealloc_device(&sdev->base_dev);
	}
	return rv;
}