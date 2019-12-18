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
struct imx7d_adc {int channel; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ IMX7D_REG_ADC_CHA_B_CNV_RSLT ; 
 scalar_t__ IMX7D_REG_ADC_CHC_D_CNV_RSLT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int imx7d_adc_read_data(struct imx7d_adc *info)
{
	u32 channel;
	u32 value;

	channel = info->channel & 0x03;

	/*
	 * channel A and B conversion result share one register,
	 * bit[27~16] is the channel B conversion result,
	 * bit[11~0] is the channel A conversion result.
	 * channel C and D is the same.
	 */
	if (channel < 2)
		value = readl(info->regs + IMX7D_REG_ADC_CHA_B_CNV_RSLT);
	else
		value = readl(info->regs + IMX7D_REG_ADC_CHC_D_CNV_RSLT);
	if (channel & 0x1)	/* channel B or D */
		value = (value >> 16) & 0xFFF;
	else			/* channel A or C */
		value &= 0xFFF;

	return value;
}