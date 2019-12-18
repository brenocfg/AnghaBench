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
struct pcf50633 {int /*<<< orphan*/  lock; TYPE_1__* irq_handler; } ;
struct TYPE_2__ {void (* handler ) (int,void*) ;void* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int PCF50633_NUM_IRQ ; 
 scalar_t__ WARN_ON (void (*) (int,void*)) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int pcf50633_register_irq(struct pcf50633 *pcf, int irq,
			void (*handler) (int, void *), void *data)
{
	if (irq < 0 || irq >= PCF50633_NUM_IRQ || !handler)
		return -EINVAL;

	if (WARN_ON(pcf->irq_handler[irq].handler))
		return -EBUSY;

	mutex_lock(&pcf->lock);
	pcf->irq_handler[irq].handler = handler;
	pcf->irq_handler[irq].data = data;
	mutex_unlock(&pcf->lock);

	return 0;
}