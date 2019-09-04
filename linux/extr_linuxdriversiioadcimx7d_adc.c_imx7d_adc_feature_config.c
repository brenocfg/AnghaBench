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
struct TYPE_2__ {int core_time_unit; int average_en; int /*<<< orphan*/  avg_num; int /*<<< orphan*/  clk_pre_div; } ;
struct imx7d_adc {TYPE_1__ adc_feature; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX7D_ADC_ANALOG_CLK_PRE_DIV_4 ; 
 int /*<<< orphan*/  IMX7D_ADC_AVERAGE_NUM_32 ; 

__attribute__((used)) static void imx7d_adc_feature_config(struct imx7d_adc *info)
{
	info->adc_feature.clk_pre_div = IMX7D_ADC_ANALOG_CLK_PRE_DIV_4;
	info->adc_feature.avg_num = IMX7D_ADC_AVERAGE_NUM_32;
	info->adc_feature.core_time_unit = 1;
	info->adc_feature.average_en = true;
}