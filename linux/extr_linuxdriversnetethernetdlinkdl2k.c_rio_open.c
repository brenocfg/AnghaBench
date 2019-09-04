#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ expires; } ;
struct netdev_private {TYPE_2__ timer; TYPE_1__* pdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int irq; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int alloc_list (struct net_device*) ; 
 int /*<<< orphan*/  dl2k_enable_int (struct netdev_private*) ; 
 int /*<<< orphan*/  free_list (struct net_device*) ; 
 scalar_t__ jiffies ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rio_hw_init (struct net_device*) ; 
 int /*<<< orphan*/  rio_hw_stop (struct net_device*) ; 
 int /*<<< orphan*/  rio_interrupt ; 
 int /*<<< orphan*/  rio_timer ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rio_open(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	const int irq = np->pdev->irq;
	int i;

	i = alloc_list(dev);
	if (i)
		return i;

	rio_hw_init(dev);

	i = request_irq(irq, rio_interrupt, IRQF_SHARED, dev->name, dev);
	if (i) {
		rio_hw_stop(dev);
		free_list(dev);
		return i;
	}

	timer_setup(&np->timer, rio_timer, 0);
	np->timer.expires = jiffies + 1 * HZ;
	add_timer(&np->timer);

	netif_start_queue (dev);

	dl2k_enable_int(np);
	return 0;
}