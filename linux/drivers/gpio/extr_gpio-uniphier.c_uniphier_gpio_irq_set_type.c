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
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 int /*<<< orphan*/  UNIPHIER_GPIO_IRQ_FLT_EN ; 
 int /*<<< orphan*/  UNIPHIER_GPIO_IRQ_MODE ; 
 int irq_chip_set_type_parent (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  uniphier_gpio_reg_update (struct uniphier_gpio_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_gpio_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct uniphier_gpio_priv *priv = data->chip_data;
	u32 mask = BIT(data->hwirq);
	u32 val = 0;

	if (type == IRQ_TYPE_EDGE_BOTH) {
		val = mask;
		type = IRQ_TYPE_EDGE_FALLING;
	}

	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_MODE, mask, val);
	/* To enable both edge detection, the noise filter must be enabled. */
	uniphier_gpio_reg_update(priv, UNIPHIER_GPIO_IRQ_FLT_EN, mask, val);

	return irq_chip_set_type_parent(data, type);
}