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
struct axp288_adc_info {int /*<<< orphan*/  regmap; int /*<<< orphan*/  ts_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP288_ADC_TS_CURRENT_ON_OFF_MASK ; 
 unsigned int AXP288_ADC_TS_CURRENT_ON_ONDEMAND ; 
 int /*<<< orphan*/  AXP288_ADC_TS_PIN_CTRL ; 
 unsigned long AXP288_GP_ADC_H ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int axp288_adc_set_ts(struct axp288_adc_info *info,
			     unsigned int mode, unsigned long address)
{
	int ret;

	/* No need to switch the current-source if the TS pin is disabled */
	if (!info->ts_enabled)
		return 0;

	/* Channels other than GPADC do not need the current source */
	if (address != AXP288_GP_ADC_H)
		return 0;

	ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
				 AXP288_ADC_TS_CURRENT_ON_OFF_MASK, mode);
	if (ret)
		return ret;

	/* When switching to the GPADC pin give things some time to settle */
	if (mode == AXP288_ADC_TS_CURRENT_ON_ONDEMAND)
		usleep_range(6000, 10000);

	return 0;
}