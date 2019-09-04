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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct flexcan_priv {int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_per; int /*<<< orphan*/  offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_rx_offload_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int flexcan_chip_start (struct net_device*) ; 
 int /*<<< orphan*/  flexcan_irq ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct flexcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int flexcan_open(struct net_device *dev)
{
	struct flexcan_priv *priv = netdev_priv(dev);
	int err;

	err = clk_prepare_enable(priv->clk_ipg);
	if (err)
		return err;

	err = clk_prepare_enable(priv->clk_per);
	if (err)
		goto out_disable_ipg;

	err = open_candev(dev);
	if (err)
		goto out_disable_per;

	err = request_irq(dev->irq, flexcan_irq, IRQF_SHARED, dev->name, dev);
	if (err)
		goto out_close;

	/* start chip and queuing */
	err = flexcan_chip_start(dev);
	if (err)
		goto out_free_irq;

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	can_rx_offload_enable(&priv->offload);
	netif_start_queue(dev);

	return 0;

 out_free_irq:
	free_irq(dev->irq, dev);
 out_close:
	close_candev(dev);
 out_disable_per:
	clk_disable_unprepare(priv->clk_per);
 out_disable_ipg:
	clk_disable_unprepare(priv->clk_ipg);

	return err;
}