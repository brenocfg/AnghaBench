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
typedef  int u32 ;
struct TYPE_2__ {int core_time_unit; } ;
struct imx7d_adc {int pre_div_num; TYPE_1__ adc_feature; } ;

/* Variables and functions */

__attribute__((used)) static u32 imx7d_adc_get_sample_rate(struct imx7d_adc *info)
{
	/* input clock is always 24MHz */
	u32 input_clk = 24000000;
	u32 analogue_core_clk;
	u32 core_time_unit = info->adc_feature.core_time_unit;
	u32 tmp;

	analogue_core_clk = input_clk / info->pre_div_num;
	tmp = (core_time_unit + 1) * 6;

	return analogue_core_clk / tmp;
}