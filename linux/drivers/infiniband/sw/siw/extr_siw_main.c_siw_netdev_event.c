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
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_LID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
#define  NETDEV_CHANGE 135 
#define  NETDEV_CHANGEADDR 134 
#define  NETDEV_CHANGEMTU 133 
#define  NETDEV_DOWN 132 
#define  NETDEV_GOING_DOWN 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  RDMA_DRIVER_SIW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 struct ib_device* ib_device_get_by_netdev (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device_queued (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  siw_dbg (struct ib_device*,char*) ; 
 int /*<<< orphan*/  siw_device_goes_down (struct siw_device*) ; 
 int /*<<< orphan*/  siw_port_event (struct siw_device*,int,int /*<<< orphan*/ ) ; 
 struct siw_device* to_siw_dev (struct ib_device*) ; 

__attribute__((used)) static int siw_netdev_event(struct notifier_block *nb, unsigned long event,
			    void *arg)
{
	struct net_device *netdev = netdev_notifier_info_to_dev(arg);
	struct ib_device *base_dev;
	struct siw_device *sdev;

	dev_dbg(&netdev->dev, "siw: event %lu\n", event);

	if (dev_net(netdev) != &init_net)
		return NOTIFY_OK;

	base_dev = ib_device_get_by_netdev(netdev, RDMA_DRIVER_SIW);
	if (!base_dev)
		return NOTIFY_OK;

	sdev = to_siw_dev(base_dev);

	switch (event) {
	case NETDEV_UP:
		sdev->state = IB_PORT_ACTIVE;
		siw_port_event(sdev, 1, IB_EVENT_PORT_ACTIVE);
		break;

	case NETDEV_GOING_DOWN:
		siw_device_goes_down(sdev);
		break;

	case NETDEV_DOWN:
		sdev->state = IB_PORT_DOWN;
		siw_port_event(sdev, 1, IB_EVENT_PORT_ERR);
		break;

	case NETDEV_REGISTER:
		/*
		 * Device registration now handled only by
		 * rdma netlink commands. So it shall be impossible
		 * to end up here with a valid siw device.
		 */
		siw_dbg(base_dev, "unexpected NETDEV_REGISTER event\n");
		break;

	case NETDEV_UNREGISTER:
		ib_unregister_device_queued(&sdev->base_dev);
		break;

	case NETDEV_CHANGEADDR:
		siw_port_event(sdev, 1, IB_EVENT_LID_CHANGE);
		break;
	/*
	 * Todo: Below netdev events are currently not handled.
	 */
	case NETDEV_CHANGEMTU:
	case NETDEV_CHANGE:
		break;

	default:
		break;
	}
	ib_device_put(&sdev->base_dev);

	return NOTIFY_OK;
}