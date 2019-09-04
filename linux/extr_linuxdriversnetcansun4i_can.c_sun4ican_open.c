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
struct sun4ican_priv {int /*<<< orphan*/  clk; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_OPEN ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct sun4ican_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  sun4i_can_interrupt ; 
 int sun4i_can_start (struct net_device*) ; 

__attribute__((used)) static int sun4ican_open(struct net_device *dev)
{
	struct sun4ican_priv *priv = netdev_priv(dev);
	int err;

	/* common open */
	err = open_candev(dev);
	if (err)
		return err;

	/* register interrupt handler */
	err = request_irq(dev->irq, sun4i_can_interrupt, 0, dev->name, dev);
	if (err) {
		netdev_err(dev, "request_irq err: %d\n", err);
		goto exit_irq;
	}

	/* turn on clocking for CAN peripheral block */
	err = clk_prepare_enable(priv->clk);
	if (err) {
		netdev_err(dev, "could not enable CAN peripheral clock\n");
		goto exit_clock;
	}

	err = sun4i_can_start(dev);
	if (err) {
		netdev_err(dev, "could not start CAN peripheral\n");
		goto exit_can_start;
	}

	can_led_event(dev, CAN_LED_EVENT_OPEN);
	netif_start_queue(dev);

	return 0;

exit_can_start:
	clk_disable_unprepare(priv->clk);
exit_clock:
	free_irq(dev->irq, dev);
exit_irq:
	close_candev(dev);
	return err;
}