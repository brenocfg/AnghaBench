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
typedef  unsigned long u32 ;
struct exynos_adc {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 unsigned long ADC_CON_EN_START ; 
 int /*<<< orphan*/  ADC_V1_CON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_V1_MUX (int /*<<< orphan*/ ) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_v1_start_conv(struct exynos_adc *info,
				     unsigned long addr)
{
	u32 con1;

	writel(addr, ADC_V1_MUX(info->regs));

	con1 = readl(ADC_V1_CON(info->regs));
	writel(con1 | ADC_CON_EN_START, ADC_V1_CON(info->regs));
}