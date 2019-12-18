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
 int IMX7D_REG_ADC_INT_CHANNEL_INT_EN ; 
 scalar_t__ IMX7D_REG_ADC_INT_EN ; 
 scalar_t__ IMX7D_REG_ADC_INT_SIG_EN ; 
 int /*<<< orphan*/  imx7d_adc_sample_rate_set (struct imx7d_adc*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imx7d_adc_hw_init(struct imx7d_adc *info)
{
	u32 cfg;

	/* power up and enable adc analogue core */
	cfg = readl(info->regs + IMX7D_REG_ADC_ADC_CFG);
	cfg &= ~(IMX7D_REG_ADC_ADC_CFG_ADC_CLK_DOWN |
		 IMX7D_REG_ADC_ADC_CFG_ADC_POWER_DOWN);
	cfg |= IMX7D_REG_ADC_ADC_CFG_ADC_EN;
	writel(cfg, info->regs + IMX7D_REG_ADC_ADC_CFG);

	/* enable channel A,B,C,D interrupt */
	writel(IMX7D_REG_ADC_INT_CHANNEL_INT_EN,
	       info->regs + IMX7D_REG_ADC_INT_SIG_EN);
	writel(IMX7D_REG_ADC_INT_CHANNEL_INT_EN,
	       info->regs + IMX7D_REG_ADC_INT_EN);

	imx7d_adc_sample_rate_set(info);
}