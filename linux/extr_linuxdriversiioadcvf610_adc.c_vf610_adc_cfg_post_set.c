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
struct vf610_adc_feature {int clk_sel; int vol_ref; scalar_t__ ovwren; } ;
struct vf610_adc {scalar_t__ regs; int /*<<< orphan*/  dev; struct vf610_adc_feature adc_feature; } ;

/* Variables and functions */
#define  VF610_ADCIOC_ADACK_SET 132 
#define  VF610_ADCIOC_ALTCLK_SET 131 
#define  VF610_ADCIOC_VR_VALT_SET 130 
#define  VF610_ADCIOC_VR_VBG_SET 129 
#define  VF610_ADCIOC_VR_VREF_SET 128 
 int VF610_ADC_ADACK_SEL ; 
 int VF610_ADC_ADHSC_EN ; 
 int VF610_ADC_ADLPC_EN ; 
 int VF610_ADC_ALTCLK_SEL ; 
 int VF610_ADC_OVWREN ; 
 int VF610_ADC_REFSEL_VALT ; 
 int VF610_ADC_REFSEL_VBG ; 
 scalar_t__ VF610_REG_ADC_CFG ; 
 scalar_t__ VF610_REG_ADC_GC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vf610_adc_cfg_post_set(struct vf610_adc *info)
{
	struct vf610_adc_feature *adc_feature = &info->adc_feature;
	int cfg_data = 0;
	int gc_data = 0;

	switch (adc_feature->clk_sel) {
	case VF610_ADCIOC_ALTCLK_SET:
		cfg_data |= VF610_ADC_ALTCLK_SEL;
		break;
	case VF610_ADCIOC_ADACK_SET:
		cfg_data |= VF610_ADC_ADACK_SEL;
		break;
	default:
		break;
	}

	/* low power set for calibration */
	cfg_data |= VF610_ADC_ADLPC_EN;

	/* enable high speed for calibration */
	cfg_data |= VF610_ADC_ADHSC_EN;

	/* voltage reference */
	switch (adc_feature->vol_ref) {
	case VF610_ADCIOC_VR_VREF_SET:
		break;
	case VF610_ADCIOC_VR_VALT_SET:
		cfg_data |= VF610_ADC_REFSEL_VALT;
		break;
	case VF610_ADCIOC_VR_VBG_SET:
		cfg_data |= VF610_ADC_REFSEL_VBG;
		break;
	default:
		dev_err(info->dev, "error voltage reference\n");
	}

	/* data overwrite enable */
	if (adc_feature->ovwren)
		cfg_data |= VF610_ADC_OVWREN;

	writel(cfg_data, info->regs + VF610_REG_ADC_CFG);
	writel(gc_data, info->regs + VF610_REG_ADC_GC);
}