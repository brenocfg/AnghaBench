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
struct max77693_muic_info {int /*<<< orphan*/  dev; TYPE_1__* max77693; } ;
typedef  enum max77693_muic_adc_debounce_time { ____Placeholder_max77693_muic_adc_debounce_time } max77693_muic_adc_debounce_time ;
struct TYPE_2__ {int /*<<< orphan*/  regmap_muic; } ;

/* Variables and functions */
#define  ADC_DEBOUNCE_TIME_10MS 131 
#define  ADC_DEBOUNCE_TIME_25MS 130 
#define  ADC_DEBOUNCE_TIME_38_62MS 129 
#define  ADC_DEBOUNCE_TIME_5MS 128 
 int EINVAL ; 
 int MAX77693_CONTROL3_ADCDBSET_SHIFT ; 
 int /*<<< orphan*/  MAX77693_MUIC_REG_CTRL3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max77693_muic_set_debounce_time(struct max77693_muic_info *info,
		enum max77693_muic_adc_debounce_time time)
{
	int ret;

	switch (time) {
	case ADC_DEBOUNCE_TIME_5MS:
	case ADC_DEBOUNCE_TIME_10MS:
	case ADC_DEBOUNCE_TIME_25MS:
	case ADC_DEBOUNCE_TIME_38_62MS:
		/*
		 * Don't touch BTLDset, JIGset when you want to change adc
		 * debounce time. If it writes other than 0 to BTLDset, JIGset
		 * muic device will be reset and loose current state.
		 */
		ret = regmap_write(info->max77693->regmap_muic,
				  MAX77693_MUIC_REG_CTRL3,
				  time << MAX77693_CONTROL3_ADCDBSET_SHIFT);
		if (ret) {
			dev_err(info->dev, "failed to set ADC debounce time\n");
			return ret;
		}
		break;
	default:
		dev_err(info->dev, "invalid ADC debounce time\n");
		return -EINVAL;
	}

	return 0;
}