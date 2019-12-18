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
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  mcp_lock; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  wq; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  tx_work; scalar_t__ tx_len; int /*<<< orphan*/ * tx_skb; scalar_t__ force_quit; struct spi_device* spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_FALLING ; 
 int WQ_FREEZABLE ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mcp251x_priv*) ; 
 int /*<<< orphan*/  mcp251x_can_ist ; 
 int mcp251x_hw_reset (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_hw_sleep (struct spi_device*) ; 
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
	unsigned long flags = 0;
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

	if (!dev_fwnode(&spi->dev))
		flags = IRQF_TRIGGER_FALLING;

	ret = request_threaded_irq(spi->irq, NULL, mcp251x_can_ist,
				   flags | IRQF_ONESHOT, dev_name(&spi->dev),
				   priv);
	if (ret) {
		dev_err(&spi->dev, "failed to acquire irq %d\n", spi->irq);
		goto out_close;
	}

	priv->wq = alloc_workqueue("mcp251x_wq", WQ_FREEZABLE | WQ_MEM_RECLAIM,
				   0);
	if (!priv->wq) {
		ret = -ENOMEM;
		goto out_clean;
	}
	INIT_WORK(&priv->tx_work, mcp251x_tx_work_handler);
	INIT_WORK(&priv->restart_work, mcp251x_restart_work_handler);

	ret = mcp251x_hw_reset(spi);
	if (ret)
		goto out_free_wq;
	ret = mcp251x_setup(net, spi);
	if (ret)
		goto out_free_wq;
	ret = mcp251x_set_normal_mode(spi);
	if (ret)
		goto out_free_wq;

	can_led_event(net, CAN_LED_EVENT_OPEN);

	netif_wake_queue(net);
	mutex_unlock(&priv->mcp_lock);

	return 0;

out_free_wq:
	destroy_workqueue(priv->wq);
out_clean:
	free_irq(spi->irq, priv);
	mcp251x_hw_sleep(spi);
out_close:
	mcp251x_power_enable(priv->transceiver, 0);
	close_candev(net);
	mutex_unlock(&priv->mcp_lock);
	return ret;
}