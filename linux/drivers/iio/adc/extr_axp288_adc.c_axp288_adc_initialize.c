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
struct dmi_system_id {scalar_t__ driver_data; } ;
struct axp288_adc_info {int ts_enabled; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_ADC_EN1 ; 
 uintptr_t AXP288_ADC_EN_MASK ; 
 uintptr_t AXP288_ADC_TS_BIAS_MASK ; 
 uintptr_t AXP288_ADC_TS_CURRENT_OFF ; 
 uintptr_t AXP288_ADC_TS_CURRENT_ON ; 
 uintptr_t AXP288_ADC_TS_CURRENT_ON_OFF_MASK ; 
 int AXP288_ADC_TS_ENABLE ; 
 int /*<<< orphan*/  AXP288_ADC_TS_PIN_CTRL ; 
 int /*<<< orphan*/  axp288_adc_ts_bias_override ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,uintptr_t) ; 

__attribute__((used)) static int axp288_adc_initialize(struct axp288_adc_info *info)
{
	const struct dmi_system_id *bias_override;
	int ret, adc_enable_val;

	bias_override = dmi_first_match(axp288_adc_ts_bias_override);
	if (bias_override) {
		ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_BIAS_MASK,
					 (uintptr_t)bias_override->driver_data);
		if (ret)
			return ret;
	}

	/*
	 * Determine if the TS pin is enabled and set the TS current-source
	 * accordingly.
	 */
	ret = regmap_read(info->regmap, AXP20X_ADC_EN1, &adc_enable_val);
	if (ret)
		return ret;

	if (adc_enable_val & AXP288_ADC_TS_ENABLE) {
		info->ts_enabled = true;
		ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_CURRENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CURRENT_ON);
	} else {
		info->ts_enabled = false;
		ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_CURRENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CURRENT_OFF);
	}
	if (ret)
		return ret;

	/* Turn on the ADC for all channels except TS, leave TS as is */
	return regmap_update_bits(info->regmap, AXP20X_ADC_EN1,
				  AXP288_ADC_EN_MASK, AXP288_ADC_EN_MASK);
}