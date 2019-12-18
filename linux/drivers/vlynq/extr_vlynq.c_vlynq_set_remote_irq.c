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
struct vlynq_device {int irq_start; int irq_end; int local_irq; int remote_irq; scalar_t__ enabled; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 

int vlynq_set_remote_irq(struct vlynq_device *dev, int virq)
{
	int irq = dev->irq_start + virq;
	if (dev->enabled)
		return -EBUSY;

	if ((irq < dev->irq_start) || (irq > dev->irq_end))
		return -EINVAL;

	if (virq == dev->local_irq)
		return -EINVAL;

	dev->remote_irq = virq;

	return 0;
}