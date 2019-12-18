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
struct irq_info {scalar_t__ type; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IRQT_EVTCHN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __unbind_from_irq (int) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int get_evtchn_to_irq (unsigned int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 struct irq_info* info_for_irq (int) ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  irq_set_chip_and_handler_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int xen_allocate_irq_dynamic () ; 
 int /*<<< orphan*/  xen_dynamic_chip ; 
 unsigned int xen_evtchn_max_channels () ; 
 int xen_irq_info_evtchn_setup (int,unsigned int) ; 

int bind_evtchn_to_irq(unsigned int evtchn)
{
	int irq;
	int ret;

	if (evtchn >= xen_evtchn_max_channels())
		return -ENOMEM;

	mutex_lock(&irq_mapping_update_lock);

	irq = get_evtchn_to_irq(evtchn);

	if (irq == -1) {
		irq = xen_allocate_irq_dynamic();
		if (irq < 0)
			goto out;

		irq_set_chip_and_handler_name(irq, &xen_dynamic_chip,
					      handle_edge_irq, "event");

		ret = xen_irq_info_evtchn_setup(irq, evtchn);
		if (ret < 0) {
			__unbind_from_irq(irq);
			irq = ret;
			goto out;
		}
		/* New interdomain events are bound to VCPU 0. */
		bind_evtchn_to_cpu(evtchn, 0);
	} else {
		struct irq_info *info = info_for_irq(irq);
		WARN_ON(info == NULL || info->type != IRQT_EVTCHN);
	}

out:
	mutex_unlock(&irq_mapping_update_lock);

	return irq;
}