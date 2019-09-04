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
struct irq_data {TYPE_1__* chip; struct irq_data* parent_data; } ;
struct TYPE_2__ {int (* irq_set_type ) (struct irq_data*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CIRQ_POL_CLR ; 
 int /*<<< orphan*/  CIRQ_POL_SET ; 
 int /*<<< orphan*/  CIRQ_SENS_CLR ; 
 int /*<<< orphan*/  CIRQ_SENS_SET ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  mtk_cirq_write_mask (struct irq_data*,int /*<<< orphan*/ ) ; 
 int stub1 (struct irq_data*,unsigned int) ; 

__attribute__((used)) static int mtk_cirq_set_type(struct irq_data *data, unsigned int type)
{
	int ret;

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_FALLING:
		mtk_cirq_write_mask(data, CIRQ_POL_CLR);
		mtk_cirq_write_mask(data, CIRQ_SENS_CLR);
		break;
	case IRQ_TYPE_EDGE_RISING:
		mtk_cirq_write_mask(data, CIRQ_POL_SET);
		mtk_cirq_write_mask(data, CIRQ_SENS_CLR);
		break;
	case IRQ_TYPE_LEVEL_LOW:
		mtk_cirq_write_mask(data, CIRQ_POL_CLR);
		mtk_cirq_write_mask(data, CIRQ_SENS_SET);
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		mtk_cirq_write_mask(data, CIRQ_POL_SET);
		mtk_cirq_write_mask(data, CIRQ_SENS_SET);
		break;
	default:
		break;
	}

	data = data->parent_data;
	ret = data->chip->irq_set_type(data, type);
	return ret;
}