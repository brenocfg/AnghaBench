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
struct gpio_rcar_priv {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSKCLR ; 
 int /*<<< orphan*/  gpio_rcar_write (struct gpio_rcar_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static void gpio_rcar_irq_enable(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct gpio_rcar_priv *p = gpiochip_get_data(gc);

	gpio_rcar_write(p, MSKCLR, BIT(irqd_to_hwirq(d)));
}