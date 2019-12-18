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
struct irq_info {scalar_t__ refcnt; } ;

/* Variables and functions */
#define  IRQT_IPI 129 
#define  IRQT_VIRQ 128 
 scalar_t__ VALID_EVTCHN (int) ; 
 unsigned int cpu_from_irq (unsigned int) ; 
 int evtchn_from_irq (unsigned int) ; 
 size_t ipi_from_irq (unsigned int) ; 
 int /*<<< orphan*/  ipi_to_irq ; 
 struct irq_info* irq_get_handler_data (unsigned int) ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int type_from_irq (unsigned int) ; 
 size_t virq_from_irq (unsigned int) ; 
 int /*<<< orphan*/  virq_to_irq ; 
 int /*<<< orphan*/  xen_evtchn_close (int) ; 
 int /*<<< orphan*/  xen_free_irq (unsigned int) ; 
 int /*<<< orphan*/  xen_irq_info_cleanup (struct irq_info*) ; 

__attribute__((used)) static void __unbind_from_irq(unsigned int irq)
{
	int evtchn = evtchn_from_irq(irq);
	struct irq_info *info = irq_get_handler_data(irq);

	if (info->refcnt > 0) {
		info->refcnt--;
		if (info->refcnt != 0)
			return;
	}

	if (VALID_EVTCHN(evtchn)) {
		unsigned int cpu = cpu_from_irq(irq);

		xen_evtchn_close(evtchn);

		switch (type_from_irq(irq)) {
		case IRQT_VIRQ:
			per_cpu(virq_to_irq, cpu)[virq_from_irq(irq)] = -1;
			break;
		case IRQT_IPI:
			per_cpu(ipi_to_irq, cpu)[ipi_from_irq(irq)] = -1;
			break;
		default:
			break;
		}

		xen_irq_info_cleanup(info);
	}

	xen_free_irq(irq);
}