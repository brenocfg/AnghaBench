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
typedef  enum vadc_scale_fn_type { ____Placeholder_vadc_scale_fn_type } vadc_scale_fn_type ;

/* Variables and functions */
 int EINVAL ; 
#define  SCALE_DEFAULT 132 
#define  SCALE_PMIC_THERM 131 
#define  SCALE_PMI_CHG_TEMP 130 
#define  SCALE_THERM_100K_PULLUP 129 
#define  SCALE_XOTHERM 128 
 int qcom_vadc_scale_chg_temp (struct vadc_linear_graph const*,struct vadc_prescale_ratio const*,int,int /*<<< orphan*/ ,int*) ; 
 int qcom_vadc_scale_die_temp (struct vadc_linear_graph const*,struct vadc_prescale_ratio const*,int,int /*<<< orphan*/ ,int*) ; 
 int qcom_vadc_scale_therm (struct vadc_linear_graph const*,struct vadc_prescale_ratio const*,int,int /*<<< orphan*/ ,int*) ; 
 int qcom_vadc_scale_volt (struct vadc_linear_graph const*,struct vadc_prescale_ratio const*,int,int /*<<< orphan*/ ,int*) ; 

int qcom_vadc_scale(enum vadc_scale_fn_type scaletype,
		    const struct vadc_linear_graph *calib_graph,
		    const struct vadc_prescale_ratio *prescale,
		    bool absolute,
		    u16 adc_code, int *result)
{
	switch (scaletype) {
	case SCALE_DEFAULT:
		return qcom_vadc_scale_volt(calib_graph, prescale,
					    absolute, adc_code,
					    result);
	case SCALE_THERM_100K_PULLUP:
	case SCALE_XOTHERM:
		return qcom_vadc_scale_therm(calib_graph, prescale,
					     absolute, adc_code,
					     result);
	case SCALE_PMIC_THERM:
		return qcom_vadc_scale_die_temp(calib_graph, prescale,
						absolute, adc_code,
						result);
	case SCALE_PMI_CHG_TEMP:
		return qcom_vadc_scale_chg_temp(calib_graph, prescale,
						absolute, adc_code,
						result);
	default:
		return -EINVAL;
	}
}