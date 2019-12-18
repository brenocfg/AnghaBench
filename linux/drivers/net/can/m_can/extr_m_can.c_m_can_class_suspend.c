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
struct m_can_classdev {TYPE_1__ can; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_SLEEPING ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  m_can_clk_stop (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_stop (struct net_device*) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (struct device*) ; 

int m_can_class_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct m_can_classdev *cdev = netdev_priv(ndev);

	if (netif_running(ndev)) {
		netif_stop_queue(ndev);
		netif_device_detach(ndev);
		m_can_stop(ndev);
		m_can_clk_stop(cdev);
	}

	pinctrl_pm_select_sleep_state(dev);

	cdev->can.state = CAN_STATE_SLEEPING;

	return 0;
}