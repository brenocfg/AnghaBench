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
struct stm32_dac_priv {int /*<<< orphan*/  vref; int /*<<< orphan*/  pclk; } ;
struct stm32_dac_common {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct stm32_dac_common* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct stm32_dac_priv* to_stm32_dac_priv (struct stm32_dac_common*) ; 

__attribute__((used)) static int stm32_dac_remove(struct platform_device *pdev)
{
	struct stm32_dac_common *common = platform_get_drvdata(pdev);
	struct stm32_dac_priv *priv = to_stm32_dac_priv(common);

	of_platform_depopulate(&pdev->dev);
	clk_disable_unprepare(priv->pclk);
	regulator_disable(priv->vref);

	return 0;
}