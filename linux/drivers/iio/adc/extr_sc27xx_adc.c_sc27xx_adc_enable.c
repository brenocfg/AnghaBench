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
struct sc27xx_adc_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC27XX_ARM_CLK_EN ; 
 int SC27XX_CLK_ADC_CLK_EN ; 
 int SC27XX_CLK_ADC_EN ; 
 int SC27XX_MODULE_ADC_EN ; 
 int /*<<< orphan*/  SC27XX_MODULE_EN ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int sc27xx_adc_scale_calibration (struct sc27xx_adc_data*,int) ; 

__attribute__((used)) static int sc27xx_adc_enable(struct sc27xx_adc_data *data)
{
	int ret;

	ret = regmap_update_bits(data->regmap, SC27XX_MODULE_EN,
				 SC27XX_MODULE_ADC_EN, SC27XX_MODULE_ADC_EN);
	if (ret)
		return ret;

	/* Enable ADC work clock and controller clock */
	ret = regmap_update_bits(data->regmap, SC27XX_ARM_CLK_EN,
				 SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN,
				 SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN);
	if (ret)
		goto disable_adc;

	/* ADC channel scales' calibration from nvmem device */
	ret = sc27xx_adc_scale_calibration(data, true);
	if (ret)
		goto disable_clk;

	ret = sc27xx_adc_scale_calibration(data, false);
	if (ret)
		goto disable_clk;

	return 0;

disable_clk:
	regmap_update_bits(data->regmap, SC27XX_ARM_CLK_EN,
			   SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN, 0);
disable_adc:
	regmap_update_bits(data->regmap, SC27XX_MODULE_EN,
			   SC27XX_MODULE_ADC_EN, 0);

	return ret;
}