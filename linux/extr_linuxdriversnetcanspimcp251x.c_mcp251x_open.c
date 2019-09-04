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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct spi_device {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct net_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  mcp_lock; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  transceiver; scalar_t__ tx_len; int /*<<< orphan*/ * tx_skb; scalar_t__ force_quit; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 int WQ_FREEZABLE ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  mcp251x_can_ist ; 
 int mcp251x_hw_reset (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_open_clean (struct net_device*) ; 
 int /*<<< orphan*/  mcp251x_power_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcp251x_restart_work_handler ; 
 int mcp251x_set_normal_mode (struct spi_device*) ; 
 int mcp251x_setup (struct net_device*,struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_tx_work_handler ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mcp251x_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct mcp251x_priv*) ; 

__attribute__((used)) static int mcp251x_open(struct net_device *net)
{
	struct mcp251x_priv *priv = netdev_priv(net);
	struct spi_device *spi = priv->spi;
	unsigned long flags = IRQF_ONESHOT | IRQF_TRIGGER_FALLING;
	int ret;

	ret = open_candev(net);
	if (ret) {
		dev_err(&spi->dev, "unable to set initial baudrate!\n");
		return ret;
	}

	mutex_lock(&priv->mcp_lock);
	mcp251x_power_enable(priv->transceiver, 1);

	priv->force_quit = 0;
	priv->tx_skb = NULL;
	priv->tx_len = 0;

	if (spi->dev.of_node)
	    flags = 0;

	ret = request_threaded_irq(spi->irq, NULL, mcp251x_can_ist,
				   flags | IRQF_ONESHOT, DEVICE_NAME, priv);
	if (ret) {
		dev_err(&spi->dev, "failed to acquire irq %d\n", spi->irq);
		mcp251x_power_enable(priv->transceiver, 0);
		close_candev(net);
		goto open_unlock;
	}

	priv->wq = alloc_workqueue("mcp251x_wq", WQ_FREEZABLE | WQ_MEM_RECLAIM,
				   0);
	INIT_WORK(&priv->tx_work, mcp251x_tx_work_handler);
	INIT_WORK(&priv->restart_work, mcp251x_restart_work_handler);

	ret = mcp251x_hw_reset(spi);
	if (ret) {
		mcp251x_open_clean(net);
		goto open_unlock;
	}
	ret = mcp251x_setup(net, spi);
	if (ret) {
		mcp251x_open_clean(net);
		goto open_unlock;
	}
	ret = mcp251x_set_normal_mode(spi);
	if (ret) {
		mcp251x_open_clean(net);
		goto open_unlock;
	}

	can_led_event(net, CAN_LED_EVENT_OPEN);

	netif_wake_queue(net);

open_unlock:
	mutex_unlock(&priv->mcp_lock);
	return ret;
}