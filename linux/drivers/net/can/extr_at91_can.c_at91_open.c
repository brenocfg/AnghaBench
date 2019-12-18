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
struct at91_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  at91_chip_start (struct net_device*) ; 
 int /*<<< orphan*/  at91_irq ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int at91_open(struct net_device *dev)
{
	struct at91_priv *priv = netdev_priv(dev);
	int err;

	err = clk_prepare_enable(priv->clk);
	if (err)
		return err;

	/* check or determine and set bittime */
	err = open_candev(dev);
	if (err)
		goto out;

	/* register interrupt handler */
	if (request_irq(dev->irq, at91_irq, IRQF_SHARED,
			dev->name, dev)) {
		err = -EAGAIN;
		goto out_close;
	}

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	/* start chip and queuing */
	at91_chip_start(dev);
	napi_enable(&priv->napi);
	netif_start_queue(dev);

	return 0;

 out_close:
	close_candev(dev);
 out:
	clk_disable_unprepare(priv->clk);

	return err;
}