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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned int GIC_DUAL_DUAL ; 
 unsigned int GIC_DUAL_SINGLE ; 
 unsigned int GIC_HWIRQ_TO_SHARED (int /*<<< orphan*/ ) ; 
 unsigned int GIC_POL_ACTIVE_HIGH ; 
 unsigned int GIC_POL_ACTIVE_LOW ; 
 unsigned int GIC_POL_FALLING_EDGE ; 
 unsigned int GIC_POL_RISING_EDGE ; 
 unsigned int GIC_TRIG_EDGE ; 
 unsigned int GIC_TRIG_LEVEL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  change_gic_dual (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  change_gic_pol (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  change_gic_trig (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  gic_edge_irq_controller ; 
 int /*<<< orphan*/  gic_level_irq_controller ; 
 int /*<<< orphan*/  gic_lock ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_handler_name_locked (struct irq_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gic_set_type(struct irq_data *d, unsigned int type)
{
	unsigned int irq, pol, trig, dual;
	unsigned long flags;

	irq = GIC_HWIRQ_TO_SHARED(d->hwirq);

	spin_lock_irqsave(&gic_lock, flags);
	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_FALLING:
		pol = GIC_POL_FALLING_EDGE;
		trig = GIC_TRIG_EDGE;
		dual = GIC_DUAL_SINGLE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		pol = GIC_POL_RISING_EDGE;
		trig = GIC_TRIG_EDGE;
		dual = GIC_DUAL_SINGLE;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		pol = 0; /* Doesn't matter */
		trig = GIC_TRIG_EDGE;
		dual = GIC_DUAL_DUAL;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		pol = GIC_POL_ACTIVE_LOW;
		trig = GIC_TRIG_LEVEL;
		dual = GIC_DUAL_SINGLE;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
	default:
		pol = GIC_POL_ACTIVE_HIGH;
		trig = GIC_TRIG_LEVEL;
		dual = GIC_DUAL_SINGLE;
		break;
	}

	change_gic_pol(irq, pol);
	change_gic_trig(irq, trig);
	change_gic_dual(irq, dual);

	if (trig == GIC_TRIG_EDGE)
		irq_set_chip_handler_name_locked(d, &gic_edge_irq_controller,
						 handle_edge_irq, NULL);
	else
		irq_set_chip_handler_name_locked(d, &gic_level_irq_controller,
						 handle_level_irq, NULL);
	spin_unlock_irqrestore(&gic_lock, flags);

	return 0;
}