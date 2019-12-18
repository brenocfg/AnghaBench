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
struct stm32_adc_priv {int /*<<< orphan*/  vdda; int /*<<< orphan*/  vref; scalar_t__ bclk; scalar_t__ aclk; TYPE_3__* cfg; TYPE_1__ common; int /*<<< orphan*/  ccr_bak; } ;
struct stm32_adc_common {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* regs; } ;
struct TYPE_5__ {scalar_t__ ccr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct stm32_adc_common* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_core_switches_supply_dis (struct stm32_adc_priv*) ; 
 struct stm32_adc_priv* to_stm32_adc_priv (struct stm32_adc_common*) ; 

__attribute__((used)) static void stm32_adc_core_hw_stop(struct device *dev)
{
	struct stm32_adc_common *common = dev_get_drvdata(dev);
	struct stm32_adc_priv *priv = to_stm32_adc_priv(common);

	/* Backup CCR that may be lost (depends on power state to achieve) */
	priv->ccr_bak = readl_relaxed(priv->common.base + priv->cfg->regs->ccr);
	if (priv->aclk)
		clk_disable_unprepare(priv->aclk);
	if (priv->bclk)
		clk_disable_unprepare(priv->bclk);
	regulator_disable(priv->vref);
	stm32_adc_core_switches_supply_dis(priv);
	regulator_disable(priv->vdda);
}