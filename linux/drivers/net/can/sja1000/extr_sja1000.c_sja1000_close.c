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
struct sja1000_priv {int flags; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_STOP ; 
 int SJA1000_CUSTOM_IRQ_HANDLER ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_reset_mode (struct net_device*) ; 

__attribute__((used)) static int sja1000_close(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);

	netif_stop_queue(dev);
	set_reset_mode(dev);

	if (!(priv->flags & SJA1000_CUSTOM_IRQ_HANDLER))
		free_irq(dev->irq, (void *)dev);

	close_candev(dev);

	can_led_event(dev, CAN_LED_EVENT_STOP);

	return 0;
}