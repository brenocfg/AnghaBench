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
struct vf610_adc_feature {int res_mode; int clk_div; int lst_adder_index; int sample_rate; int /*<<< orphan*/  clk_sel; } ;
struct vf610_adc {scalar_t__ regs; int /*<<< orphan*/  dev; struct vf610_adc_feature adc_feature; } ;

/* Variables and functions */
#define  VF610_ADCIOC_BUSCLK_SET 141 
#define  VF610_ADCK_CYCLES_13 140 
#define  VF610_ADCK_CYCLES_17 139 
#define  VF610_ADCK_CYCLES_21 138 
#define  VF610_ADCK_CYCLES_25 137 
#define  VF610_ADCK_CYCLES_3 136 
#define  VF610_ADCK_CYCLES_5 135 
#define  VF610_ADCK_CYCLES_7 134 
#define  VF610_ADCK_CYCLES_9 133 
 int VF610_ADC_ADCCLK_MASK ; 
 int VF610_ADC_ADLSMP_LONG ; 
 int VF610_ADC_ADSTS_LONG ; 
 int VF610_ADC_ADSTS_NORMAL ; 
 int VF610_ADC_ADSTS_SHORT ; 
 int VF610_ADC_AVGEN ; 
 int VF610_ADC_AVGS_16 ; 
 int VF610_ADC_AVGS_32 ; 
 int VF610_ADC_AVGS_8 ; 
 int VF610_ADC_AVGS_MASK ; 
 int VF610_ADC_BUSCLK2_SEL ; 
 int VF610_ADC_CLK_DIV2 ; 
 int VF610_ADC_CLK_DIV4 ; 
 int VF610_ADC_CLK_DIV8 ; 
 int VF610_ADC_CLK_MASK ; 
 int VF610_ADC_MODE_BIT10 ; 
 int VF610_ADC_MODE_BIT12 ; 
 int VF610_ADC_MODE_BIT8 ; 
 int VF610_ADC_MODE_MASK ; 
#define  VF610_ADC_SAMPLE_1 132 
#define  VF610_ADC_SAMPLE_16 131 
#define  VF610_ADC_SAMPLE_32 130 
#define  VF610_ADC_SAMPLE_4 129 
#define  VF610_ADC_SAMPLE_8 128 
 scalar_t__ VF610_REG_ADC_CFG ; 
 scalar_t__ VF610_REG_ADC_GC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vf610_adc_sample_set(struct vf610_adc *info)
{
	struct vf610_adc_feature *adc_feature = &(info->adc_feature);
	int cfg_data, gc_data;

	cfg_data = readl(info->regs + VF610_REG_ADC_CFG);
	gc_data = readl(info->regs + VF610_REG_ADC_GC);

	/* resolution mode */
	cfg_data &= ~VF610_ADC_MODE_MASK;
	switch (adc_feature->res_mode) {
	case 8:
		cfg_data |= VF610_ADC_MODE_BIT8;
		break;
	case 10:
		cfg_data |= VF610_ADC_MODE_BIT10;
		break;
	case 12:
		cfg_data |= VF610_ADC_MODE_BIT12;
		break;
	default:
		dev_err(info->dev, "error resolution mode\n");
		break;
	}

	/* clock select and clock divider */
	cfg_data &= ~(VF610_ADC_CLK_MASK | VF610_ADC_ADCCLK_MASK);
	switch (adc_feature->clk_div) {
	case 1:
		break;
	case 2:
		cfg_data |= VF610_ADC_CLK_DIV2;
		break;
	case 4:
		cfg_data |= VF610_ADC_CLK_DIV4;
		break;
	case 8:
		cfg_data |= VF610_ADC_CLK_DIV8;
		break;
	case 16:
		switch (adc_feature->clk_sel) {
		case VF610_ADCIOC_BUSCLK_SET:
			cfg_data |= VF610_ADC_BUSCLK2_SEL | VF610_ADC_CLK_DIV8;
			break;
		default:
			dev_err(info->dev, "error clk divider\n");
			break;
		}
		break;
	}

	/*
	 * Set ADLSMP and ADSTS based on the Long Sample Time Adder value
	 * determined.
	 */
	switch (adc_feature->lst_adder_index) {
	case VF610_ADCK_CYCLES_3:
		break;
	case VF610_ADCK_CYCLES_5:
		cfg_data |= VF610_ADC_ADSTS_SHORT;
		break;
	case VF610_ADCK_CYCLES_7:
		cfg_data |= VF610_ADC_ADSTS_NORMAL;
		break;
	case VF610_ADCK_CYCLES_9:
		cfg_data |= VF610_ADC_ADSTS_LONG;
		break;
	case VF610_ADCK_CYCLES_13:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		break;
	case VF610_ADCK_CYCLES_17:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		cfg_data |= VF610_ADC_ADSTS_SHORT;
		break;
	case VF610_ADCK_CYCLES_21:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		cfg_data |= VF610_ADC_ADSTS_NORMAL;
		break;
	case VF610_ADCK_CYCLES_25:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		cfg_data |= VF610_ADC_ADSTS_NORMAL;
		break;
	default:
		dev_err(info->dev, "error in sample time select\n");
	}

	/* update hardware average selection */
	cfg_data &= ~VF610_ADC_AVGS_MASK;
	gc_data &= ~VF610_ADC_AVGEN;
	switch (adc_feature->sample_rate) {
	case VF610_ADC_SAMPLE_1:
		break;
	case VF610_ADC_SAMPLE_4:
		gc_data |= VF610_ADC_AVGEN;
		break;
	case VF610_ADC_SAMPLE_8:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_8;
		break;
	case VF610_ADC_SAMPLE_16:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_16;
		break;
	case VF610_ADC_SAMPLE_32:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_32;
		break;
	default:
		dev_err(info->dev,
			"error hardware sample average select\n");
	}

	writel(cfg_data, info->regs + VF610_REG_ADC_CFG);
	writel(gc_data, info->regs + VF610_REG_ADC_GC);
}