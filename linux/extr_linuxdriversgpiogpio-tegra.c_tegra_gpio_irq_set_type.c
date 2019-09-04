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
typedef  unsigned int u32 ;
struct tegra_gpio_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  gc; } ;
struct tegra_gpio_bank {int /*<<< orphan*/ * lvl_lock; struct tegra_gpio_info* tgi; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GPIO_BIT (unsigned int) ; 
 int /*<<< orphan*/  GPIO_INT_LVL (struct tegra_gpio_info*,unsigned int) ; 
 unsigned int GPIO_INT_LVL_EDGE_BOTH ; 
 unsigned int GPIO_INT_LVL_EDGE_FALLING ; 
 unsigned int GPIO_INT_LVL_EDGE_RISING ; 
 unsigned int GPIO_INT_LVL_LEVEL_HIGH ; 
 unsigned int GPIO_INT_LVL_LEVEL_LOW ; 
 unsigned int GPIO_INT_LVL_MASK ; 
 int /*<<< orphan*/  GPIO_MSK_OE (struct tegra_gpio_info*,unsigned int) ; 
 unsigned int GPIO_PORT (unsigned int) ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int gpiochip_lock_as_irq (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct tegra_gpio_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_gpio_disable (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  tegra_gpio_enable (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  tegra_gpio_mask_write (struct tegra_gpio_info*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int tegra_gpio_readl (struct tegra_gpio_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_gpio_writel (struct tegra_gpio_info*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	unsigned int gpio = d->hwirq, port = GPIO_PORT(gpio), lvl_type;
	struct tegra_gpio_bank *bank = irq_data_get_irq_chip_data(d);
	struct tegra_gpio_info *tgi = bank->tgi;
	unsigned long flags;
	u32 val;
	int ret;

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		lvl_type = GPIO_INT_LVL_EDGE_RISING;
		break;

	case IRQ_TYPE_EDGE_FALLING:
		lvl_type = GPIO_INT_LVL_EDGE_FALLING;
		break;

	case IRQ_TYPE_EDGE_BOTH:
		lvl_type = GPIO_INT_LVL_EDGE_BOTH;
		break;

	case IRQ_TYPE_LEVEL_HIGH:
		lvl_type = GPIO_INT_LVL_LEVEL_HIGH;
		break;

	case IRQ_TYPE_LEVEL_LOW:
		lvl_type = GPIO_INT_LVL_LEVEL_LOW;
		break;

	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&bank->lvl_lock[port], flags);

	val = tegra_gpio_readl(tgi, GPIO_INT_LVL(tgi, gpio));
	val &= ~(GPIO_INT_LVL_MASK << GPIO_BIT(gpio));
	val |= lvl_type << GPIO_BIT(gpio);
	tegra_gpio_writel(tgi, val, GPIO_INT_LVL(tgi, gpio));

	spin_unlock_irqrestore(&bank->lvl_lock[port], flags);

	tegra_gpio_mask_write(tgi, GPIO_MSK_OE(tgi, gpio), gpio, 0);
	tegra_gpio_enable(tgi, gpio);

	ret = gpiochip_lock_as_irq(&tgi->gc, gpio);
	if (ret) {
		dev_err(tgi->dev,
			"unable to lock Tegra GPIO %u as IRQ\n", gpio);
		tegra_gpio_disable(tgi, gpio);
		return ret;
	}

	if (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(d, handle_level_irq);
	else if (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		irq_set_handler_locked(d, handle_edge_irq);

	return 0;
}