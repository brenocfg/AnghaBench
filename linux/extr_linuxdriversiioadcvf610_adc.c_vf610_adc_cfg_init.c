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
struct vf610_adc_feature {int calibration; int ovwren; int res_mode; int sample_rate; int /*<<< orphan*/  conv_mode; int /*<<< orphan*/  vol_ref; int /*<<< orphan*/  clk_sel; } ;
struct vf610_adc {struct vf610_adc_feature adc_feature; } ;

/* Variables and functions */
 int /*<<< orphan*/  VF610_ADCIOC_BUSCLK_SET ; 
 int /*<<< orphan*/  VF610_ADCIOC_VR_VREF_SET ; 
 int /*<<< orphan*/  VF610_ADC_CONV_LOW_POWER ; 
 int /*<<< orphan*/  vf610_adc_calculate_rates (struct vf610_adc*) ; 

__attribute__((used)) static inline void vf610_adc_cfg_init(struct vf610_adc *info)
{
	struct vf610_adc_feature *adc_feature = &info->adc_feature;

	/* set default Configuration for ADC controller */
	adc_feature->clk_sel = VF610_ADCIOC_BUSCLK_SET;
	adc_feature->vol_ref = VF610_ADCIOC_VR_VREF_SET;

	adc_feature->calibration = true;
	adc_feature->ovwren = true;

	adc_feature->res_mode = 12;
	adc_feature->sample_rate = 1;

	adc_feature->conv_mode = VF610_ADC_CONV_LOW_POWER;

	vf610_adc_calculate_rates(info);
}