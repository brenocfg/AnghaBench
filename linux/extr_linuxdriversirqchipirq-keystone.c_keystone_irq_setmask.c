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
struct keystone_irq_device {int /*<<< orphan*/  mask; int /*<<< orphan*/  dev; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct keystone_irq_device* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void keystone_irq_setmask(struct irq_data *d)
{
	struct keystone_irq_device *kirq = irq_data_get_irq_chip_data(d);

	kirq->mask |= BIT(d->hwirq);
	dev_dbg(kirq->dev, "mask %lu [%x]\n", d->hwirq, kirq->mask);
}