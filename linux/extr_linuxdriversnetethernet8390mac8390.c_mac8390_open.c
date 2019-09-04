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

/* Variables and functions */
 int /*<<< orphan*/  __ei_interrupt ; 
 int /*<<< orphan*/  __ei_open (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static int mac8390_open(struct net_device *dev)
{
	int err;

	__ei_open(dev);
	err = request_irq(dev->irq, __ei_interrupt, 0, "8390 Ethernet", dev);
	if (err)
		pr_err("%s: unable to get IRQ %d\n", dev->name, dev->irq);
	return err;
}