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
struct irq_data {int hwirq; } ;
typedef  enum pdc_irq_config_bits { ____Placeholder_pdc_irq_config_bits } pdc_irq_config_bits ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  IRQ_i_CFG ; 
 int PDC_EDGE_DUAL ; 
 int PDC_EDGE_FALLING ; 
 int PDC_EDGE_RISING ; 
 int PDC_LEVEL_HIGH ; 
 int PDC_LEVEL_LOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int irq_chip_set_type_parent (struct irq_data*,unsigned int) ; 
 int /*<<< orphan*/  pdc_reg_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qcom_pdc_gic_set_type(struct irq_data *d, unsigned int type)
{
	int pin_out = d->hwirq;
	enum pdc_irq_config_bits pdc_type;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		pdc_type = PDC_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		pdc_type = PDC_EDGE_FALLING;
		type = IRQ_TYPE_EDGE_RISING;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		pdc_type = PDC_EDGE_DUAL;
		type = IRQ_TYPE_EDGE_RISING;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		pdc_type = PDC_LEVEL_HIGH;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		pdc_type = PDC_LEVEL_LOW;
		type = IRQ_TYPE_LEVEL_HIGH;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	pdc_reg_write(IRQ_i_CFG, pin_out, pdc_type);

	return irq_chip_set_type_parent(d, type);
}