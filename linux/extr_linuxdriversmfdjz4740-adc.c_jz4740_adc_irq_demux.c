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
typedef  int uint8_t ;
struct irq_desc {int dummy; } ;
struct irq_chip_generic {scalar_t__ irq_base; scalar_t__ reg_base; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ JZ_REG_ADC_STATUS ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 
 struct irq_chip_generic* irq_desc_get_handler_data (struct irq_desc*) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static void jz4740_adc_irq_demux(struct irq_desc *desc)
{
	struct irq_chip_generic *gc = irq_desc_get_handler_data(desc);
	uint8_t status;
	unsigned int i;

	status = readb(gc->reg_base + JZ_REG_ADC_STATUS);

	for (i = 0; i < 5; ++i) {
		if (status & BIT(i))
			generic_handle_irq(gc->irq_base + i);
	}
}