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
struct net_device {int /*<<< orphan*/  irq; } ;
struct m_can_classdev {int /*<<< orphan*/ * tx_wq; int /*<<< orphan*/ * tx_skb; scalar_t__ is_peripheral; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  m_can_clk_stop (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_stop (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int m_can_close(struct net_device *dev)
{
	struct m_can_classdev *cdev = netdev_priv(dev);

	netif_stop_queue(dev);

	if (!cdev->is_peripheral)
		napi_disable(&cdev->napi);

	m_can_stop(dev);
	m_can_clk_stop(cdev);
	free_irq(dev->irq, dev);

	if (cdev->is_peripheral) {
		cdev->tx_skb = NULL;
		destroy_workqueue(cdev->tx_wq);
		cdev->tx_wq = NULL;
	}

	close_candev(dev);
	can_led_event(dev, CAN_LED_EVENT_STOP);

	return 0;
}