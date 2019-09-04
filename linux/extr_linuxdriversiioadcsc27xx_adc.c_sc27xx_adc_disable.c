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
struct sc27xx_adc_data {int /*<<< orphan*/  regmap; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SC27XX_ADC_INT_EN ; 
 int SC27XX_ADC_IRQ_EN ; 
 scalar_t__ SC27XX_ARM_CLK_EN ; 
 int SC27XX_CLK_ADC_CLK_EN ; 
 int SC27XX_CLK_ADC_EN ; 
 int SC27XX_MODULE_ADC_EN ; 
 scalar_t__ SC27XX_MODULE_EN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc27xx_adc_disable(void *_data)
{
	struct sc27xx_adc_data *data = _data;

	regmap_update_bits(data->regmap, data->base + SC27XX_ADC_INT_EN,
			   SC27XX_ADC_IRQ_EN, 0);

	/* Disable ADC work clock and controller clock */
	regmap_update_bits(data->regmap, SC27XX_ARM_CLK_EN,
			   SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN, 0);

	regmap_update_bits(data->regmap, SC27XX_MODULE_EN,
			   SC27XX_MODULE_ADC_EN, 0);
}