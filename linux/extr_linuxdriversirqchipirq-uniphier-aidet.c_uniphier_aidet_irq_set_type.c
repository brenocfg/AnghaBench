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
struct uniphier_aidet_priv {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; struct uniphier_aidet_priv* chip_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int irq_chip_set_type_parent (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  uniphier_aidet_detconf_update (struct uniphier_aidet_priv*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int uniphier_aidet_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct uniphier_aidet_priv *priv = data->chip_data;
	unsigned int val;

	/* enable inverter for active low triggers */
	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_LEVEL_HIGH:
		val = 0;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		val = 1;
		type = IRQ_TYPE_EDGE_RISING;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		val = 1;
		type = IRQ_TYPE_LEVEL_HIGH;
		break;
	default:
		return -EINVAL;
	}

	uniphier_aidet_detconf_update(priv, data->hwirq, val);

	return irq_chip_set_type_parent(data, type);
}