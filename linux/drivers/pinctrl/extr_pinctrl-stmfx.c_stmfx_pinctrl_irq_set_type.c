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
typedef  size_t u32 ;
struct stmfx_pinctrl {size_t* irq_gpi_evt; size_t* irq_gpi_type; size_t* irq_toggle_edge; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_NONE ; 
 size_t get_mask (int /*<<< orphan*/ ) ; 
 size_t get_reg (int /*<<< orphan*/ ) ; 
 struct stmfx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmfx_pinctrl_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	struct stmfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);
	u32 reg = get_reg(data->hwirq);
	u32 mask = get_mask(data->hwirq);

	if (type == IRQ_TYPE_NONE)
		return -EINVAL;

	if (type & IRQ_TYPE_EDGE_BOTH) {
		pctl->irq_gpi_evt[reg] |= mask;
		irq_set_handler_locked(data, handle_edge_irq);
	} else {
		pctl->irq_gpi_evt[reg] &= ~mask;
		irq_set_handler_locked(data, handle_level_irq);
	}

	if ((type & IRQ_TYPE_EDGE_RISING) || (type & IRQ_TYPE_LEVEL_HIGH))
		pctl->irq_gpi_type[reg] |= mask;
	else
		pctl->irq_gpi_type[reg] &= ~mask;

	/*
	 * In case of (type & IRQ_TYPE_EDGE_BOTH), we need to know current
	 * GPIO value to set the right edge trigger. But in atomic context
	 * here we can't access registers over I2C. That's why (type &
	 * IRQ_TYPE_EDGE_BOTH) will be managed in .irq_sync_unlock.
	 */

	if ((type & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH)
		pctl->irq_toggle_edge[reg] |= mask;
	else
		pctl->irq_toggle_edge[reg] &= mask;

	return 0;
}