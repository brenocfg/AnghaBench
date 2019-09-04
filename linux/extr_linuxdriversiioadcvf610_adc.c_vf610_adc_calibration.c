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
struct TYPE_2__ {int calibration; } ;
struct vf610_adc {TYPE_1__ adc_feature; int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int VF610_ADC_AIEN ; 
 int VF610_ADC_CAL ; 
 int VF610_ADC_CALF ; 
 int VF610_ADC_CONV_DISABLE ; 
 int /*<<< orphan*/  VF610_ADC_TIMEOUT ; 
 scalar_t__ VF610_REG_ADC_GC ; 
 scalar_t__ VF610_REG_ADC_GS ; 
 scalar_t__ VF610_REG_ADC_HC0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vf610_adc_calibration(struct vf610_adc *info)
{
	int adc_gc, hc_cfg;

	if (!info->adc_feature.calibration)
		return;

	/* enable calibration interrupt */
	hc_cfg = VF610_ADC_AIEN | VF610_ADC_CONV_DISABLE;
	writel(hc_cfg, info->regs + VF610_REG_ADC_HC0);

	adc_gc = readl(info->regs + VF610_REG_ADC_GC);
	writel(adc_gc | VF610_ADC_CAL, info->regs + VF610_REG_ADC_GC);

	if (!wait_for_completion_timeout(&info->completion, VF610_ADC_TIMEOUT))
		dev_err(info->dev, "Timeout for adc calibration\n");

	adc_gc = readl(info->regs + VF610_REG_ADC_GS);
	if (adc_gc & VF610_ADC_CALF)
		dev_err(info->dev, "ADC calibration failed\n");

	info->adc_feature.calibration = false;
}