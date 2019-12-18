#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xircom_private {int open; TYPE_1__* pdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int const) ; 
 struct xircom_private* netdev_priv (struct net_device*) ; 
 int request_irq (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  xircom_interrupt ; 
 int /*<<< orphan*/  xircom_up (struct xircom_private*) ; 

__attribute__((used)) static int xircom_open(struct net_device *dev)
{
	struct xircom_private *xp = netdev_priv(dev);
	const int irq = xp->pdev->irq;
	int retval;

	netdev_info(dev, "xircom cardbus adaptor found, using irq %i\n", irq);
	retval = request_irq(irq, xircom_interrupt, IRQF_SHARED, dev->name, dev);
	if (retval)
		return retval;

	xircom_up(xp);
	xp->open = 1;

	return 0;
}