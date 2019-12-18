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
struct exynos_adc {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ADC_CON_EN_START ; 
 int /*<<< orphan*/  ADC_V2_CON1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_V2_CON2 (int /*<<< orphan*/ ) ; 
 int ADC_V2_CON2_ACH_MASK ; 
 int ADC_V2_CON2_ACH_SEL (unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_v2_start_conv(struct exynos_adc *info,
				     unsigned long addr)
{
	u32 con1, con2;

	con2 = readl(ADC_V2_CON2(info->regs));
	con2 &= ~ADC_V2_CON2_ACH_MASK;
	con2 |= ADC_V2_CON2_ACH_SEL(addr);
	writel(con2, ADC_V2_CON2(info->regs));

	con1 = readl(ADC_V2_CON1(info->regs));
	writel(con1 | ADC_CON_EN_START, ADC_V2_CON1(info->regs));
}