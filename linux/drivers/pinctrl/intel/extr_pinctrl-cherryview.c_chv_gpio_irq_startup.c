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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct chv_pinctrl {unsigned int* intr_lines; } ;
typedef  int /*<<< orphan*/  irq_flow_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_PADCTRL0 ; 
 int CHV_PADCTRL0_INTSEL_MASK ; 
 int CHV_PADCTRL0_INTSEL_SHIFT ; 
 int /*<<< orphan*/  CHV_PADCTRL1 ; 
 int CHV_PADCTRL1_INTWAKECFG_LEVEL ; 
 scalar_t__ IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  chv_gpio_irq_unmask (struct irq_data*) ; 
 int /*<<< orphan*/  chv_lock ; 
 int /*<<< orphan*/  chv_padreg (struct chv_pinctrl*,unsigned int,int /*<<< orphan*/ ) ; 
 struct chv_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_get_trigger_type (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned chv_gpio_irq_startup(struct irq_data *d)
{
	/*
	 * Check if the interrupt has been requested with 0 as triggering
	 * type. In that case it is assumed that the current values
	 * programmed to the hardware are used (e.g BIOS configured
	 * defaults).
	 *
	 * In that case ->irq_set_type() will never be called so we need to
	 * read back the values from hardware now, set correct flow handler
	 * and update mappings before the interrupt is being used.
	 */
	if (irqd_get_trigger_type(d) == IRQ_TYPE_NONE) {
		struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
		struct chv_pinctrl *pctrl = gpiochip_get_data(gc);
		unsigned int pin = irqd_to_hwirq(d);
		irq_flow_handler_t handler;
		unsigned long flags;
		u32 intsel, value;

		raw_spin_lock_irqsave(&chv_lock, flags);
		intsel = readl(chv_padreg(pctrl, pin, CHV_PADCTRL0));
		intsel &= CHV_PADCTRL0_INTSEL_MASK;
		intsel >>= CHV_PADCTRL0_INTSEL_SHIFT;

		value = readl(chv_padreg(pctrl, pin, CHV_PADCTRL1));
		if (value & CHV_PADCTRL1_INTWAKECFG_LEVEL)
			handler = handle_level_irq;
		else
			handler = handle_edge_irq;

		if (!pctrl->intr_lines[intsel]) {
			irq_set_handler_locked(d, handler);
			pctrl->intr_lines[intsel] = pin;
		}
		raw_spin_unlock_irqrestore(&chv_lock, flags);
	}

	chv_gpio_irq_unmask(d);
	return 0;
}