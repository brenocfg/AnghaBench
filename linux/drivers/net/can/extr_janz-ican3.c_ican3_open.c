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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ican3_dev {TYPE_1__ can; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int ican3_set_bus_state (struct ican3_dev*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct ican3_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 

__attribute__((used)) static int ican3_open(struct net_device *ndev)
{
	struct ican3_dev *mod = netdev_priv(ndev);
	int ret;

	/* open the CAN layer */
	ret = open_candev(ndev);
	if (ret) {
		netdev_err(mod->ndev, "unable to start CAN layer\n");
		return ret;
	}

	/* bring the bus online */
	ret = ican3_set_bus_state(mod, true);
	if (ret) {
		netdev_err(mod->ndev, "unable to set bus-on\n");
		close_candev(ndev);
		return ret;
	}

	/* start up the network device */
	mod->can.state = CAN_STATE_ERROR_ACTIVE;
	netif_start_queue(ndev);

	return 0;
}