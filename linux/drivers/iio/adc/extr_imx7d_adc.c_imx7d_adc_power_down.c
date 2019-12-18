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
typedef  int u32 ;
struct imx7d_adc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ IMX7D_REG_ADC_ADC_CFG ; 
 int IMX7D_REG_ADC_ADC_CFG_ADC_CLK_DOWN ; 
 int IMX7D_REG_ADC_ADC_CFG_ADC_EN ; 
 int IMX7D_REG_ADC_ADC_CFG_ADC_POWER_DOWN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imx7d_adc_power_down(struct imx7d_adc *info)
{
	u32 adc_cfg;

	adc_cfg = readl(info->regs + IMX7D_REG_ADC_ADC_CFG);
	adc_cfg |= IMX7D_REG_ADC_ADC_CFG_ADC_CLK_DOWN |
		   IMX7D_REG_ADC_ADC_CFG_ADC_POWER_DOWN;
	adc_cfg &= ~IMX7D_REG_ADC_ADC_CFG_ADC_EN;
	writel(adc_cfg, info->regs + IMX7D_REG_ADC_ADC_CFG);
}