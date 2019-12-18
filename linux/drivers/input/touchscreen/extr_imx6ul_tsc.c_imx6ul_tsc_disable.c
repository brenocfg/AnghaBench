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
typedef  int /*<<< orphan*/  u32 ;
struct imx6ul_tsc {scalar_t__ adc_regs; scalar_t__ tsc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_CONV_DISABLE ; 
 scalar_t__ REG_ADC_HC0 ; 
 scalar_t__ REG_TSC_FLOW_CONTROL ; 
 int /*<<< orphan*/  TSC_DISABLE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imx6ul_tsc_disable(struct imx6ul_tsc *tsc)
{
	u32 tsc_flow;
	u32 adc_cfg;

	/* TSC controller enters to idle status */
	tsc_flow = readl(tsc->tsc_regs + REG_TSC_FLOW_CONTROL);
	tsc_flow |= TSC_DISABLE;
	writel(tsc_flow, tsc->tsc_regs + REG_TSC_FLOW_CONTROL);

	/* ADC controller enters to stop mode */
	adc_cfg = readl(tsc->adc_regs + REG_ADC_HC0);
	adc_cfg |= ADC_CONV_DISABLE;
	writel(adc_cfg, tsc->adc_regs + REG_ADC_HC0);
}