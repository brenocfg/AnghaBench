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
struct rxe_dev {int /*<<< orphan*/  ib_dev; } ;
struct notifier_block {int dummy; } ;
struct net_device {unsigned long name; unsigned long mtu; } ;

/* Variables and functions */
#define  NETDEV_CHANGE 137 
#define  NETDEV_CHANGEADDR 136 
#define  NETDEV_CHANGEMTU 135 
#define  NETDEV_CHANGENAME 134 
#define  NETDEV_DOWN 133 
#define  NETDEV_FEAT_CHANGE 132 
#define  NETDEV_GOING_DOWN 131 
#define  NETDEV_REBOOT 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ib_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device_queued (int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long) ; 
 struct rxe_dev* rxe_get_dev_from_net (struct net_device*) ; 
 int /*<<< orphan*/  rxe_port_down (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_port_up (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_set_mtu (struct rxe_dev*,unsigned long) ; 
 int /*<<< orphan*/  rxe_set_port_state (struct rxe_dev*) ; 

__attribute__((used)) static int rxe_notify(struct notifier_block *not_blk,
		      unsigned long event,
		      void *arg)
{
	struct net_device *ndev = netdev_notifier_info_to_dev(arg);
	struct rxe_dev *rxe = rxe_get_dev_from_net(ndev);

	if (!rxe)
		return NOTIFY_OK;

	switch (event) {
	case NETDEV_UNREGISTER:
		ib_unregister_device_queued(&rxe->ib_dev);
		break;
	case NETDEV_UP:
		rxe_port_up(rxe);
		break;
	case NETDEV_DOWN:
		rxe_port_down(rxe);
		break;
	case NETDEV_CHANGEMTU:
		pr_info("%s changed mtu to %d\n", ndev->name, ndev->mtu);
		rxe_set_mtu(rxe, ndev->mtu);
		break;
	case NETDEV_CHANGE:
		rxe_set_port_state(rxe);
		break;
	case NETDEV_REBOOT:
	case NETDEV_GOING_DOWN:
	case NETDEV_CHANGEADDR:
	case NETDEV_CHANGENAME:
	case NETDEV_FEAT_CHANGE:
	default:
		pr_info("ignoring netdev event = %ld for %s\n",
			event, ndev->name);
		break;
	}

	ib_device_put(&rxe->ib_dev);
	return NOTIFY_OK;
}