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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32MP1_SYSCFG_ANASWVDD_MASK ; 
 int /*<<< orphan*/  STM32MP1_SYSCFG_PMCSETR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int regmap_write (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int stm32_adc_core_switches_supply_en(struct stm32_adc_priv *priv,
					     struct device *dev)
{
	int ret;

	/*
	 * On STM32H7 and STM32MP1, the ADC inputs are multiplexed with analog
	 * switches (via PCSEL) which have reduced performances when their
	 * supply is below 2.7V (vdda by default):
	 * - Voltage booster can be used, to get full ADC performances
	 *   (increases power consumption).
	 * - Vdd can be used to supply them, if above 2.7V (STM32MP1 only).
	 *
	 * Recommended settings for ANASWVDD and EN_BOOSTER:
	 * - vdda < 2.7V but vdd > 2.7V: ANASWVDD = 1, EN_BOOSTER = 0 (stm32mp1)
	 * - vdda < 2.7V and vdd < 2.7V: ANASWVDD = 0, EN_BOOSTER = 1
	 * - vdda >= 2.7V:               ANASWVDD = 0, EN_BOOSTER = 0 (default)
	 */
	if (priv->vdda_uv < 2700000) {
		if (priv->syscfg && priv->vdd_uv > 2700000) {
			ret = regulator_enable(priv->vdd);
			if (ret < 0) {
				dev_err(dev, "vdd enable failed %d\n", ret);
				return ret;
			}

			ret = regmap_write(priv->syscfg,
					   STM32MP1_SYSCFG_PMCSETR,
					   STM32MP1_SYSCFG_ANASWVDD_MASK);
			if (ret < 0) {
				regulator_disable(priv->vdd);
				dev_err(dev, "vdd select failed, %d\n", ret);
				return ret;
			}
			dev_dbg(dev, "analog switches supplied by vdd\n");

			return 0;
		}

		if (priv->booster) {
			/*
			 * This is optional, as this is a trade-off between
			 * analog performance and power consumption.
			 */
			ret = regulator_enable(priv->booster);
			if (ret < 0) {
				dev_err(dev, "booster enable failed %d\n", ret);
				return ret;
			}
			dev_dbg(dev, "analog switches supplied by booster\n");

			return 0;
		}
	}

	/* Fallback using vdda (default), nothing to do */
	dev_dbg(dev, "analog switches supplied by vdda (%d uV)\n",
		priv->vdda_uv);

	return 0;
}