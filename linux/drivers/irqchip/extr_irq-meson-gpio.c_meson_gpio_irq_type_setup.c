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
typedef  int /*<<< orphan*/  u32 ;
struct meson_gpio_irq_controller {int /*<<< orphan*/  lock; TYPE_1__* params; } ;
struct TYPE_2__ {int /*<<< orphan*/  support_edge_both; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  REG_BOTH_EDGE (unsigned int) ; 
 int /*<<< orphan*/  REG_EDGE_POL ; 
 int /*<<< orphan*/  REG_EDGE_POL_EDGE (unsigned int) ; 
 int /*<<< orphan*/  REG_EDGE_POL_LOW (unsigned int) ; 
 int /*<<< orphan*/  REG_EDGE_POL_MASK (unsigned int) ; 
 unsigned int meson_gpio_irq_get_channel_idx (struct meson_gpio_irq_controller*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meson_gpio_irq_update_bits (struct meson_gpio_irq_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int meson_gpio_irq_type_setup(struct meson_gpio_irq_controller *ctl,
				     unsigned int type,
				     u32 *channel_hwirq)
{
	u32 val = 0;
	unsigned int idx;

	idx = meson_gpio_irq_get_channel_idx(ctl, channel_hwirq);

	/*
	 * The controller has a filter block to operate in either LEVEL or
	 * EDGE mode, then signal is sent to the GIC. To enable LEVEL_LOW and
	 * EDGE_FALLING support (which the GIC does not support), the filter
	 * block is also able to invert the input signal it gets before
	 * providing it to the GIC.
	 */
	type &= IRQ_TYPE_SENSE_MASK;

	/*
	 * New controller support EDGE_BOTH trigger. This setting takes
	 * precedence over the other edge/polarity settings
	 */
	if (type == IRQ_TYPE_EDGE_BOTH) {
		if (!ctl->params->support_edge_both)
			return -EINVAL;

		val |= REG_BOTH_EDGE(idx);
	} else {
		if (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))
			val |= REG_EDGE_POL_EDGE(idx);

		if (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_EDGE_FALLING))
			val |= REG_EDGE_POL_LOW(idx);
	}

	spin_lock(&ctl->lock);

	meson_gpio_irq_update_bits(ctl, REG_EDGE_POL,
				   REG_EDGE_POL_MASK(idx), val);

	spin_unlock(&ctl->lock);

	return 0;
}