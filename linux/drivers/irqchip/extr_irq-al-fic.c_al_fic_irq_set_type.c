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
struct irq_data {int dummy; } ;
struct irq_chip_generic {struct al_fic* private; } ;
struct al_fic {scalar_t__ state; int /*<<< orphan*/  name; } ;
typedef  enum al_fic_state { ____Placeholder_al_fic_state } al_fic_state ;

/* Variables and functions */
 int AL_FIC_CONFIGURED_LEVEL ; 
 int AL_FIC_CONFIGURED_RISING_EDGE ; 
 scalar_t__ AL_FIC_UNCONFIGURED ; 
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  al_fic_set_trigger (struct al_fic*,struct irq_chip_generic*,int) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,...) ; 

__attribute__((used)) static int al_fic_irq_set_type(struct irq_data *data, unsigned int flow_type)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	struct al_fic *fic = gc->private;
	enum al_fic_state new_state;
	int ret = 0;

	irq_gc_lock(gc);

	if (((flow_type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_LEVEL_HIGH) &&
	    ((flow_type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_EDGE_RISING)) {
		pr_debug("fic doesn't support flow type %d\n", flow_type);
		ret = -EINVAL;
		goto err;
	}

	new_state = (flow_type & IRQ_TYPE_LEVEL_HIGH) ?
		AL_FIC_CONFIGURED_LEVEL : AL_FIC_CONFIGURED_RISING_EDGE;

	/*
	 * A given FIC instance can be either all level or all edge triggered.
	 * This is generally fixed depending on what pieces of HW it's wired up
	 * to.
	 *
	 * We configure it based on the sensitivity of the first source
	 * being setup, and reject any subsequent attempt at configuring it in a
	 * different way.
	 */
	if (fic->state == AL_FIC_UNCONFIGURED) {
		al_fic_set_trigger(fic, gc, new_state);
	} else if (fic->state != new_state) {
		pr_debug("fic %s state already configured to %d\n",
			 fic->name, fic->state);
		ret = -EINVAL;
		goto err;
	}

err:
	irq_gc_unlock(gc);

	return ret;
}