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
struct sc27xx_adc_data {int /*<<< orphan*/  completion; int /*<<< orphan*/  value; scalar_t__ base; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 scalar_t__ SC27XX_ADC_DATA ; 
 int /*<<< orphan*/  SC27XX_ADC_DATA_MASK ; 
 scalar_t__ SC27XX_ADC_INT_CLR ; 
 int /*<<< orphan*/  SC27XX_ADC_IRQ_CLR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sc27xx_adc_isr(int irq, void *dev_id)
{
	struct sc27xx_adc_data *data = dev_id;
	int ret;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_INT_CLR,
				 SC27XX_ADC_IRQ_CLR, SC27XX_ADC_IRQ_CLR);
	if (ret)
		return IRQ_RETVAL(ret);

	ret = regmap_read(data->regmap, data->base + SC27XX_ADC_DATA,
			  &data->value);
	if (ret)
		return IRQ_RETVAL(ret);

	data->value &= SC27XX_ADC_DATA_MASK;
	complete(&data->completion);

	return IRQ_HANDLED;
}