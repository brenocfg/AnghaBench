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
typedef  int u32 ;
struct armada_37xx_pinctrl {int /*<<< orphan*/  irq_lock; scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int GPIO_PER_REG ; 
 scalar_t__ INPUT_VAL ; 
 scalar_t__ IRQ_POL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int armada_37xx_edge_both_irq_swap_pol(struct armada_37xx_pinctrl *info,
					     u32 pin_idx)
{
	u32 reg_idx = pin_idx / GPIO_PER_REG;
	u32 bit_num = pin_idx % GPIO_PER_REG;
	u32 p, l, ret;
	unsigned long flags;

	regmap_read(info->regmap, INPUT_VAL + 4*reg_idx, &l);

	spin_lock_irqsave(&info->irq_lock, flags);
	p = readl(info->base + IRQ_POL + 4 * reg_idx);
	if ((p ^ l) & (1 << bit_num)) {
		/*
		 * For the gpios which are used for both-edge irqs, when their
		 * interrupts happen, their input levels are changed,
		 * yet their interrupt polarities are kept in old values, we
		 * should synchronize their interrupt polarities; for example,
		 * at first a gpio's input level is low and its interrupt
		 * polarity control is "Detect rising edge", then the gpio has
		 * a interrupt , its level turns to high, we should change its
		 * polarity control to "Detect falling edge" correspondingly.
		 */
		p ^= 1 << bit_num;
		writel(p, info->base + IRQ_POL + 4 * reg_idx);
		ret = 0;
	} else {
		/* Spurious irq */
		ret = -1;
	}

	spin_unlock_irqrestore(&info->irq_lock, flags);
	return ret;
}