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
struct adc5_data {int dummy; } ;

/* Variables and functions */
 int qcom_vadc_scale_code_voltage_factor (int /*<<< orphan*/ ,struct vadc_prescale_ratio const*,struct adc5_data const*,int) ; 

__attribute__((used)) static int qcom_vadc_scale_hw_calib_volt(
				const struct vadc_prescale_ratio *prescale,
				const struct adc5_data *data,
				u16 adc_code, int *result_uv)
{
	*result_uv = qcom_vadc_scale_code_voltage_factor(adc_code,
				prescale, data, 1);

	return 0;
}