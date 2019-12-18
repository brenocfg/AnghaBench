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
typedef  int /*<<< orphan*/  u32 ;
struct meson_gpio_irq_controller {int /*<<< orphan*/  lock; int /*<<< orphan*/ * channel_irqs; int /*<<< orphan*/  channel_map; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned int NUM_CHANNEL ; 
 unsigned long REG_PIN_SEL_SHIFT (unsigned int) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int meson_gpio_irq_channel_to_reg (unsigned int) ; 
 int /*<<< orphan*/  meson_gpio_irq_update_bits (struct meson_gpio_irq_controller*,unsigned int,int,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
meson_gpio_irq_request_channel(struct meson_gpio_irq_controller *ctl,
			       unsigned long  hwirq,
			       u32 **channel_hwirq)
{
	unsigned int reg, idx;

	spin_lock(&ctl->lock);

	/* Find a free channel */
	idx = find_first_zero_bit(ctl->channel_map, NUM_CHANNEL);
	if (idx >= NUM_CHANNEL) {
		spin_unlock(&ctl->lock);
		pr_err("No channel available\n");
		return -ENOSPC;
	}

	/* Mark the channel as used */
	set_bit(idx, ctl->channel_map);

	/*
	 * Setup the mux of the channel to route the signal of the pad
	 * to the appropriate input of the GIC
	 */
	reg = meson_gpio_irq_channel_to_reg(idx);
	meson_gpio_irq_update_bits(ctl, reg,
				   0xff << REG_PIN_SEL_SHIFT(idx),
				   hwirq << REG_PIN_SEL_SHIFT(idx));

	/*
	 * Get the hwirq number assigned to this channel through
	 * a pointer the channel_irq table. The added benifit of this
	 * method is that we can also retrieve the channel index with
	 * it, using the table base.
	 */
	*channel_hwirq = &(ctl->channel_irqs[idx]);

	spin_unlock(&ctl->lock);

	pr_debug("hwirq %lu assigned to channel %d - irq %u\n",
		 hwirq, idx, **channel_hwirq);

	return 0;
}