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
struct stm32_adc_priv {int /*<<< orphan*/  vref; scalar_t__ aclk; scalar_t__ bclk; } ;
struct stm32_adc_common {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct stm32_adc_common* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_adc_irq_remove (struct platform_device*,struct stm32_adc_priv*) ; 
 struct stm32_adc_priv* to_stm32_adc_priv (struct stm32_adc_common*) ; 

__attribute__((used)) static int stm32_adc_remove(struct platform_device *pdev)
{
	struct stm32_adc_common *common = platform_get_drvdata(pdev);
	struct stm32_adc_priv *priv = to_stm32_adc_priv(common);

	of_platform_depopulate(&pdev->dev);
	stm32_adc_irq_remove(pdev, priv);
	if (priv->bclk)
		clk_disable_unprepare(priv->bclk);
	if (priv->aclk)
		clk_disable_unprepare(priv->aclk);
	regulator_disable(priv->vref);

	return 0;
}