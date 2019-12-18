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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int bind_evtchn_to_irq (unsigned int) ; 
 int request_irq (int,int /*<<< orphan*/ ,unsigned long,char const*,void*) ; 
 int /*<<< orphan*/  unbind_from_irq (int) ; 

int bind_evtchn_to_irqhandler(unsigned int evtchn,
			      irq_handler_t handler,
			      unsigned long irqflags,
			      const char *devname, void *dev_id)
{
	int irq, retval;

	irq = bind_evtchn_to_irq(evtchn);
	if (irq < 0)
		return irq;
	retval = request_irq(irq, handler, irqflags, devname, dev_id);
	if (retval != 0) {
		unbind_from_irq(irq);
		return retval;
	}

	return irq;
}