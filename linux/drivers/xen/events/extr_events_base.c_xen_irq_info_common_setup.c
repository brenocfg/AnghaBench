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
struct irq_info {scalar_t__ type; unsigned int irq; unsigned int evtchn; unsigned short cpu; } ;
typedef  enum xen_irq_type { ____Placeholder_xen_irq_type } xen_irq_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IRQT_UNBOUND ; 
 int IRQ_NOAUTOEN ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  irq_clear_status_flags (unsigned int,int) ; 
 int set_evtchn_to_irq (unsigned int,unsigned int) ; 
 int xen_evtchn_port_setup (struct irq_info*) ; 

__attribute__((used)) static int xen_irq_info_common_setup(struct irq_info *info,
				     unsigned irq,
				     enum xen_irq_type type,
				     unsigned evtchn,
				     unsigned short cpu)
{
	int ret;

	BUG_ON(info->type != IRQT_UNBOUND && info->type != type);

	info->type = type;
	info->irq = irq;
	info->evtchn = evtchn;
	info->cpu = cpu;

	ret = set_evtchn_to_irq(evtchn, irq);
	if (ret < 0)
		return ret;

	irq_clear_status_flags(irq, IRQ_NOREQUEST|IRQ_NOAUTOEN);

	return xen_evtchn_port_setup(info);
}