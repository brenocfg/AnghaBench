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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct ifi_canfd_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  ifi_canfd_isr ; 
 int /*<<< orphan*/  ifi_canfd_start (struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ifi_canfd_open(struct net_device *ndev)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	int ret;

	ret = open_candev(ndev);
	if (ret) {
		netdev_err(ndev, "Failed to open CAN device\n");
		return ret;
	}

	/* Register interrupt handler */
	ret = request_irq(ndev->irq, ifi_canfd_isr, IRQF_SHARED,
			  ndev->name, ndev);
	if (ret < 0) {
		netdev_err(ndev, "Failed to request interrupt\n");
		goto err_irq;
	}

	ifi_canfd_start(ndev);

	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	napi_enable(&priv->napi);
	netif_start_queue(ndev);

	return 0;
err_irq:
	close_candev(ndev);
	return ret;
}