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
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  irq; } ;
struct atmel_private {scalar_t__ bus_type; int /*<<< orphan*/  firmware; int /*<<< orphan*/  management_timer; } ;

/* Variables and functions */
 scalar_t__ BUS_TYPE_PCCARD ; 
 int /*<<< orphan*/  GCR ; 
 int /*<<< orphan*/  atmel_write16 (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void stop_atmel_card(struct net_device *dev)
{
	struct atmel_private *priv = netdev_priv(dev);

	/* put a brick on it... */
	if (priv->bus_type == BUS_TYPE_PCCARD)
		atmel_write16(dev, GCR, 0x0060);
	atmel_write16(dev, GCR, 0x0040);

	del_timer_sync(&priv->management_timer);
	unregister_netdev(dev);
	remove_proc_entry("driver/atmel", NULL);
	free_irq(dev->irq, dev);
	kfree(priv->firmware);
	release_region(dev->base_addr, 32);
	free_netdev(dev);
}