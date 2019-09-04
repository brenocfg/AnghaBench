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
typedef  int /*<<< orphan*/  u32 ;
struct exynos_adc {int /*<<< orphan*/  regs; TYPE_1__* data; int /*<<< orphan*/  pmu_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_offset; scalar_t__ needs_adc_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_CON_EN_START ; 
 int /*<<< orphan*/  ADC_V2_CON1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_v2_exit_hw(struct exynos_adc *info)
{
	u32 con;

	if (info->data->needs_adc_phy)
		regmap_write(info->pmu_map, info->data->phy_offset, 0);

	con = readl(ADC_V2_CON1(info->regs));
	con &= ~ADC_CON_EN_START;
	writel(con, ADC_V2_CON1(info->regs));
}