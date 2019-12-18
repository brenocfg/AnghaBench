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
struct stm32_adc_priv {int vdda_uv; int vdd_uv; scalar_t__ booster; scalar_t__ vdd; scalar_t__ syscfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32MP1_SYSCFG_ANASWVDD_MASK ; 
 int /*<<< orphan*/  STM32MP1_SYSCFG_PMCCLRR ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static void stm32_adc_core_switches_supply_dis(struct stm32_adc_priv *priv)
{
	if (priv->vdda_uv < 2700000) {
		if (priv->syscfg && priv->vdd_uv > 2700000) {
			regmap_write(priv->syscfg, STM32MP1_SYSCFG_PMCCLRR,
				     STM32MP1_SYSCFG_ANASWVDD_MASK);
			regulator_disable(priv->vdd);
			return;
		}
		if (priv->booster)
			regulator_disable(priv->booster);
	}
}