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
struct TYPE_2__ {size_t avg_num; } ;
struct imx7d_adc {int channel; scalar_t__ regs; TYPE_1__ adc_feature; } ;

/* Variables and functions */
 int IMX7D_EACH_CHANNEL_REG_OFFSET ; 
 scalar_t__ IMX7D_REG_ADC_CHANNEL_CFG2_BASE ; 
 int IMX7D_REG_ADC_CH_CFG1_CHANNEL_AVG_EN ; 
 int IMX7D_REG_ADC_CH_CFG1_CHANNEL_EN ; 
 int IMX7D_REG_ADC_CH_CFG1_CHANNEL_SEL (int) ; 
 int IMX7D_REG_ADC_CH_CFG1_CHANNEL_SINGLE ; 
 int* imx7d_adc_average_num ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imx7d_adc_channel_set(struct imx7d_adc *info)
{
	u32 cfg1 = 0;
	u32 cfg2;
	u32 channel;

	channel = info->channel;

	/* the channel choose single conversion, and enable average mode */
	cfg1 |= (IMX7D_REG_ADC_CH_CFG1_CHANNEL_EN |
		 IMX7D_REG_ADC_CH_CFG1_CHANNEL_SINGLE |
		 IMX7D_REG_ADC_CH_CFG1_CHANNEL_AVG_EN);

	/*
	 * physical channel 0 chose logical channel A
	 * physical channel 1 chose logical channel B
	 * physical channel 2 chose logical channel C
	 * physical channel 3 chose logical channel D
	 */
	cfg1 |= IMX7D_REG_ADC_CH_CFG1_CHANNEL_SEL(channel);

	/*
	 * read register REG_ADC_CH_A\B\C\D_CFG2, according to the
	 * channel chosen
	 */
	cfg2 = readl(info->regs + IMX7D_EACH_CHANNEL_REG_OFFSET * channel +
		     IMX7D_REG_ADC_CHANNEL_CFG2_BASE);

	cfg2 |= imx7d_adc_average_num[info->adc_feature.avg_num];

	/*
	 * write the register REG_ADC_CH_A\B\C\D_CFG2, according to
	 * the channel chosen
	 */
	writel(cfg2, info->regs + IMX7D_EACH_CHANNEL_REG_OFFSET * channel +
	       IMX7D_REG_ADC_CHANNEL_CFG2_BASE);
	writel(cfg1, info->regs + IMX7D_EACH_CHANNEL_REG_OFFSET * channel);
}