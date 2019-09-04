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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned int EHV_PIC_INFO (int /*<<< orphan*/ ) ; 
 int IRQ_SET_MASK_OK_NOCOPY ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  VECPRI_POLARITY_MASK ; 
 int /*<<< orphan*/  VECPRI_SENSE_MASK ; 
 int /*<<< orphan*/  ehv_pic_lock ; 
 unsigned int ehv_pic_type_to_vecpri (unsigned int) ; 
 int /*<<< orphan*/  ev_int_get_config (unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ev_int_set_config (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int virq_to_hw (int /*<<< orphan*/ ) ; 

int ehv_pic_set_irq_type(struct irq_data *d, unsigned int flow_type)
{
	unsigned int src = virq_to_hw(d->irq);
	unsigned int vecpri, vold, vnew, prio, cpu_dest;
	unsigned long flags;

	if (flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_LEVEL_LOW;

	irqd_set_trigger_type(d, flow_type);

	vecpri = ehv_pic_type_to_vecpri(flow_type);

	spin_lock_irqsave(&ehv_pic_lock, flags);
	ev_int_get_config(src, &vold, &prio, &cpu_dest);
	vnew = vold & ~(EHV_PIC_INFO(VECPRI_POLARITY_MASK) |
			EHV_PIC_INFO(VECPRI_SENSE_MASK));
	vnew |= vecpri;

	/*
	 * TODO : Add specific interface call for platform to set
	 * individual interrupt priorities.
	 * platform currently using static/default priority for all ints
	 */

	prio = 8;

	ev_int_set_config(src, vecpri, prio, cpu_dest);

	spin_unlock_irqrestore(&ehv_pic_lock, flags);
	return IRQ_SET_MASK_OK_NOCOPY;
}