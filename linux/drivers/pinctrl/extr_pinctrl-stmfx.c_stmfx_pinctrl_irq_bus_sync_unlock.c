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
typedef  size_t u32 ;
struct stmfx_pinctrl {size_t* irq_toggle_edge; size_t* irq_gpi_type; size_t* irq_gpi_evt; size_t* irq_gpi_src; int /*<<< orphan*/  lock; TYPE_1__* stmfx; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_GPIO_REGS ; 
 int /*<<< orphan*/  STMFX_REG_IRQ_GPI_EVT ; 
 int /*<<< orphan*/  STMFX_REG_IRQ_GPI_SRC ; 
 int /*<<< orphan*/  STMFX_REG_IRQ_GPI_TYPE ; 
 size_t get_mask (int /*<<< orphan*/ ) ; 
 size_t get_reg (int /*<<< orphan*/ ) ; 
 struct stmfx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ stmfx_gpio_get (struct gpio_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmfx_pinctrl_irq_bus_sync_unlock(struct irq_data *data)
{
	struct gpio_chip *gpio_chip = irq_data_get_irq_chip_data(data);
	struct stmfx_pinctrl *pctl = gpiochip_get_data(gpio_chip);
	u32 reg = get_reg(data->hwirq);
	u32 mask = get_mask(data->hwirq);

	/*
	 * In case of IRQ_TYPE_EDGE_BOTH), read the current GPIO value
	 * (this couldn't be done in .irq_set_type because of atomic context)
	 * to set the right irq trigger type.
	 */
	if (pctl->irq_toggle_edge[reg] & mask) {
		if (stmfx_gpio_get(gpio_chip, data->hwirq))
			pctl->irq_gpi_type[reg] &= ~mask;
		else
			pctl->irq_gpi_type[reg] |= mask;
	}

	regmap_bulk_write(pctl->stmfx->map, STMFX_REG_IRQ_GPI_EVT,
			  pctl->irq_gpi_evt, NR_GPIO_REGS);
	regmap_bulk_write(pctl->stmfx->map, STMFX_REG_IRQ_GPI_TYPE,
			  pctl->irq_gpi_type, NR_GPIO_REGS);
	regmap_bulk_write(pctl->stmfx->map, STMFX_REG_IRQ_GPI_SRC,
			  pctl->irq_gpi_src, NR_GPIO_REGS);

	mutex_unlock(&pctl->lock);
}