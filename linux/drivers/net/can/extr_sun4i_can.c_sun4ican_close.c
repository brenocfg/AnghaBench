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
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct sun4ican_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  sun4i_can_stop (struct net_device*) ; 

__attribute__((used)) static int sun4ican_close(struct net_device *dev)
{
	struct sun4ican_priv *priv = netdev_priv(dev);

	netif_stop_queue(dev);
	sun4i_can_stop(dev);
	clk_disable_unprepare(priv->clk);

	free_irq(dev->irq, dev);
	close_candev(dev);
	can_led_event(dev, CAN_LED_EVENT_STOP);

	return 0;
}