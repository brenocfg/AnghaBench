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
struct stm32_dfsdm {int dummy; } ;
struct dfsdm_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  aclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct dfsdm_priv* to_stm32_dfsdm_priv (struct stm32_dfsdm*) ; 

__attribute__((used)) static int stm32_dfsdm_clk_prepare_enable(struct stm32_dfsdm *dfsdm)
{
	struct dfsdm_priv *priv = to_stm32_dfsdm_priv(dfsdm);
	int ret;

	ret = clk_prepare_enable(priv->clk);
	if (ret || !priv->aclk)
		return ret;

	ret = clk_prepare_enable(priv->aclk);
	if (ret)
		clk_disable_unprepare(priv->clk);

	return ret;
}