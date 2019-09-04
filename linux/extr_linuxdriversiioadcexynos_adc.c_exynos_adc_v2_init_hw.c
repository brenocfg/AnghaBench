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
struct exynos_adc {int /*<<< orphan*/  regs; TYPE_1__* data; int /*<<< orphan*/  pmu_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_offset; scalar_t__ needs_adc_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_V2_CON1 (int /*<<< orphan*/ ) ; 
 int ADC_V2_CON1_SOFT_RESET ; 
 int /*<<< orphan*/  ADC_V2_CON2 (int /*<<< orphan*/ ) ; 
 int ADC_V2_CON2_C_TIME (int /*<<< orphan*/ ) ; 
 int ADC_V2_CON2_ESEL ; 
 int ADC_V2_CON2_HIGHF ; 
 int ADC_V2_CON2_OSEL ; 
 int /*<<< orphan*/  ADC_V2_INT_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_v2_init_hw(struct exynos_adc *info)
{
	u32 con1, con2;

	if (info->data->needs_adc_phy)
		regmap_write(info->pmu_map, info->data->phy_offset, 1);

	con1 = ADC_V2_CON1_SOFT_RESET;
	writel(con1, ADC_V2_CON1(info->regs));

	con2 = ADC_V2_CON2_OSEL | ADC_V2_CON2_ESEL |
		ADC_V2_CON2_HIGHF | ADC_V2_CON2_C_TIME(0);
	writel(con2, ADC_V2_CON2(info->regs));

	/* Enable interrupts */
	writel(1, ADC_V2_INT_EN(info->regs));
}