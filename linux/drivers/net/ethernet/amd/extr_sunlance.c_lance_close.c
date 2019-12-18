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
struct lance_private {int /*<<< orphan*/  multicast_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  STOP_LANCE (struct lance_private*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int lance_close(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);

	netif_stop_queue(dev);
	del_timer_sync(&lp->multicast_timer);

	STOP_LANCE(lp);

	free_irq(dev->irq, (void *) dev);
	return 0;
}