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
struct sc27xx_fgu_data {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ SC27XX_FGU_CURRENT ; 
 scalar_t__ SC27XX_FGU_CUR_BASIC_ADC ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int sc27xx_fgu_adc_to_current (struct sc27xx_fgu_data*,scalar_t__) ; 

__attribute__((used)) static int sc27xx_fgu_get_current(struct sc27xx_fgu_data *data, int *val)
{
	int ret, cur;

	ret = regmap_read(data->regmap, data->base + SC27XX_FGU_CURRENT, &cur);
	if (ret)
		return ret;

	/*
	 * It is ADC values reading from registers which need to convert to
	 * corresponding current values.
	 */
	*val = sc27xx_fgu_adc_to_current(data, cur - SC27XX_FGU_CUR_BASIC_ADC);

	return 0;
}