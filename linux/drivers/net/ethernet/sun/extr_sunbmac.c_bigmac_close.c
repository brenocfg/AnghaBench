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
struct bigmac {scalar_t__ timer_ticks; int /*<<< orphan*/  timer_state; int /*<<< orphan*/  bigmac_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  asleep ; 
 int /*<<< orphan*/  bigmac_clean_rings (struct bigmac*) ; 
 int /*<<< orphan*/  bigmac_stop (struct bigmac*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bigmac*) ; 
 struct bigmac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bigmac_close(struct net_device *dev)
{
	struct bigmac *bp = netdev_priv(dev);

	del_timer(&bp->bigmac_timer);
	bp->timer_state = asleep;
	bp->timer_ticks = 0;

	bigmac_stop(bp);
	bigmac_clean_rings(bp);
	free_irq(dev->irq, bp);
	return 0;
}