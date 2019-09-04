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
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/ * irq_count ; 
 int irq_first ; 
 unsigned int num_irqs ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sysfs_notify (struct kobject*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static irqreturn_t ab8500_debug_handler(int irq, void *data)
{
	char buf[16];
	struct kobject *kobj = (struct kobject *)data;
	unsigned int irq_abb = irq - irq_first;

	if (irq_abb < num_irqs)
		irq_count[irq_abb]++;
	/*
	 * This makes it possible to use poll for events (EPOLLPRI | EPOLLERR)
	 * from userspace on sysfs file named <irq-nr>
	 */
	sprintf(buf, "%d", irq);
	sysfs_notify(kobj, NULL, buf);

	return IRQ_HANDLED;
}