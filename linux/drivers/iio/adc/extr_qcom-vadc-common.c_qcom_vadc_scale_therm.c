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
typedef  int /*<<< orphan*/  u16 ;
struct vadc_prescale_ratio {int dummy; } ;
struct vadc_linear_graph {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adcmap_100k_104ef_104fb ; 
 int /*<<< orphan*/  div64_s64 (int /*<<< orphan*/ ,int) ; 
 int qcom_vadc_map_voltage_temp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qcom_vadc_scale_calib (struct vadc_linear_graph const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcom_vadc_scale_therm(const struct vadc_linear_graph *calib_graph,
				 const struct vadc_prescale_ratio *prescale,
				 bool absolute, u16 adc_code,
				 int *result_mdec)
{
	s64 voltage = 0;
	int ret;

	qcom_vadc_scale_calib(calib_graph, adc_code, absolute, &voltage);

	if (absolute)
		voltage = div64_s64(voltage, 1000);

	ret = qcom_vadc_map_voltage_temp(adcmap_100k_104ef_104fb,
					 ARRAY_SIZE(adcmap_100k_104ef_104fb),
					 voltage, result_mdec);
	if (ret)
		return ret;

	*result_mdec *= 1000;

	return 0;
}