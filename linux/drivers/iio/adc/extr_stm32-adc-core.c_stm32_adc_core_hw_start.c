#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ base; } ;
struct stm32_adc_priv {int vdda_uv; int /*<<< orphan*/  vdda; int /*<<< orphan*/  vref; scalar_t__ bclk; TYPE_3__* cfg; TYPE_1__ common; int /*<<< orphan*/  ccr_bak; scalar_t__ aclk; } ;
struct stm32_adc_common {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* regs; } ;
struct TYPE_5__ {scalar_t__ ccr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct stm32_adc_common* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_core_switches_supply_dis (struct stm32_adc_priv*) ; 
 int stm32_adc_core_switches_supply_en (struct stm32_adc_priv*,struct device*) ; 
 struct stm32_adc_priv* to_stm32_adc_priv (struct stm32_adc_common*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stm32_adc_core_hw_start(struct device *dev)
{
	struct stm32_adc_common *common = dev_get_drvdata(dev);
	struct stm32_adc_priv *priv = to_stm32_adc_priv(common);
	int ret;

	ret = regulator_enable(priv->vdda);
	if (ret < 0) {
		dev_err(dev, "vdda enable failed %d\n", ret);
		return ret;
	}

	ret = regulator_get_voltage(priv->vdda);
	if (ret < 0) {
		dev_err(dev, "vdda get voltage failed, %d\n", ret);
		goto err_vdda_disable;
	}
	priv->vdda_uv = ret;

	ret = stm32_adc_core_switches_supply_en(priv, dev);
	if (ret < 0)
		goto err_vdda_disable;

	ret = regulator_enable(priv->vref);
	if (ret < 0) {
		dev_err(dev, "vref enable failed\n");
		goto err_switches_dis;
	}

	if (priv->bclk) {
		ret = clk_prepare_enable(priv->bclk);
		if (ret < 0) {
			dev_err(dev, "bus clk enable failed\n");
			goto err_regulator_disable;
		}
	}

	if (priv->aclk) {
		ret = clk_prepare_enable(priv->aclk);
		if (ret < 0) {
			dev_err(dev, "adc clk enable failed\n");
			goto err_bclk_disable;
		}
	}

	writel_relaxed(priv->ccr_bak, priv->common.base + priv->cfg->regs->ccr);

	return 0;

err_bclk_disable:
	if (priv->bclk)
		clk_disable_unprepare(priv->bclk);
err_regulator_disable:
	regulator_disable(priv->vref);
err_switches_dis:
	stm32_adc_core_switches_supply_dis(priv);
err_vdda_disable:
	regulator_disable(priv->vdda);

	return ret;
}