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
struct uniphier_gpio_priv {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; struct uniphier_gpio_priv* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIPHIER_GPIO_IRQ_EN ; 
 void irq_chip_unmask_parent (struct irq_data*) ; 
 int /*<<< orphan*/  uniphier_gpio_reg_update (struct uniphier_gpio_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uniphier_gpio_irq_unmask(struct irq_data *data)
{
	struct uniphier_gpio_priv *priv = data->chip_data;
	u32 mask = BIT(data->hwirq);

	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_EN, mask, mask);

	return irq_chip_unmask_parent(data);
}