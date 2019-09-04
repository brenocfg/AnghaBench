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
struct exynos_adc {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_V1_INTCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_v1_clear_irq(struct exynos_adc *info)
{
	writel(1, ADC_V1_INTCLR(info->regs));
}