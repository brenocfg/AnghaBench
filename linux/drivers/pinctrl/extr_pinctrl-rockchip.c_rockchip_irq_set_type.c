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
struct rockchip_pin_bank {int toggle_edge_mode; int /*<<< orphan*/  clk; int /*<<< orphan*/  slock; scalar_t__ reg_base; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct irq_chip_generic {scalar_t__ reg_base; struct rockchip_pin_bank* private; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ GPIO_EXT_PORT ; 
 scalar_t__ GPIO_INTTYPE_LEVEL ; 
 scalar_t__ GPIO_INT_POLARITY ; 
 scalar_t__ GPIO_SWPORT_DDR ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  RK_FUNC_GPIO ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int rockchip_set_mux (struct rockchip_pin_bank*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int rockchip_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct rockchip_pin_bank *bank = gc->private;
	u32 mask = BIT(d->hwirq);
	u32 polarity;
	u32 level;
	u32 data;
	unsigned long flags;
	int ret;

	/* make sure the pin is configured as gpio input */
	ret = rockchip_set_mux(bank, d->hwirq, RK_FUNC_GPIO);
	if (ret < 0)
		return ret;

	clk_enable(bank->clk);
	raw_spin_lock_irqsave(&bank->slock, flags);

	data = readl_relaxed(bank->reg_base + GPIO_SWPORT_DDR);
	data &= ~mask;
	writel_relaxed(data, bank->reg_base + GPIO_SWPORT_DDR);

	raw_spin_unlock_irqrestore(&bank->slock, flags);

	if (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	else
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_lock_irqsave(&bank->slock, flags);
	irq_gc_lock(gc);

	level = readl_relaxed(gc->reg_base + GPIO_INTTYPE_LEVEL);
	polarity = readl_relaxed(gc->reg_base + GPIO_INT_POLARITY);

	switch (type) {
	case IRQ_TYPE_EDGE_BOTH:
		bank->toggle_edge_mode |= mask;
		level |= mask;

		/*
		 * Determine gpio state. If 1 next interrupt should be falling
		 * otherwise rising.
		 */
		data = readl(bank->reg_base + GPIO_EXT_PORT);
		if (data & mask)
			polarity &= ~mask;
		else
			polarity |= mask;
		break;
	case IRQ_TYPE_EDGE_RISING:
		bank->toggle_edge_mode &= ~mask;
		level |= mask;
		polarity |= mask;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		bank->toggle_edge_mode &= ~mask;
		level |= mask;
		polarity &= ~mask;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		bank->toggle_edge_mode &= ~mask;
		level &= ~mask;
		polarity |= mask;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		bank->toggle_edge_mode &= ~mask;
		level &= ~mask;
		polarity &= ~mask;
		break;
	default:
		irq_gc_unlock(gc);
		raw_spin_unlock_irqrestore(&bank->slock, flags);
		clk_disable(bank->clk);
		return -EINVAL;
	}

	writel_relaxed(level, gc->reg_base + GPIO_INTTYPE_LEVEL);
	writel_relaxed(polarity, gc->reg_base + GPIO_INT_POLARITY);

	irq_gc_unlock(gc);
	raw_spin_unlock_irqrestore(&bank->slock, flags);
	clk_disable(bank->clk);

	return 0;
}