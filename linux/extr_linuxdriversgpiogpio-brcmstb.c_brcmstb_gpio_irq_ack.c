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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int /*<<< orphan*/  (* write_reg ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
struct brcmstb_gpio_priv {scalar_t__ reg_base; } ;
struct brcmstb_gpio_bank {int /*<<< orphan*/  id; struct brcmstb_gpio_priv* parent_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ GIO_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmstb_gpio_hwirq_to_offset (int /*<<< orphan*/ ,struct brcmstb_gpio_bank*) ; 
 struct brcmstb_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmstb_gpio_irq_ack(struct irq_data *d)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	struct brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(d->hwirq, bank));

	gc->write_reg(priv->reg_base + GIO_STAT(bank->id), mask);
}