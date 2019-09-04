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
struct ican3_dev {int /*<<< orphan*/  echoq; int /*<<< orphan*/  ndev; TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int ican3_set_bus_state (struct ican3_dev*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct ican3_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ican3_stop(struct net_device *ndev)
{
	struct ican3_dev *mod = netdev_priv(ndev);
	int ret;

	/* stop the network device xmit routine */
	netif_stop_queue(ndev);
	mod->can.state = CAN_STATE_STOPPED;

	/* bring the bus offline, stop receiving packets */
	ret = ican3_set_bus_state(mod, false);
	if (ret) {
		netdev_err(mod->ndev, "unable to set bus-off\n");
		return ret;
	}

	/* drop all outstanding echo skbs */
	skb_queue_purge(&mod->echoq);

	/* close the CAN layer */
	close_candev(ndev);
	return 0;
}