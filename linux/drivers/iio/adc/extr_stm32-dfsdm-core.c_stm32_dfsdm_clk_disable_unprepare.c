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
struct dfsdm_priv {scalar_t__ clk; scalar_t__ aclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct dfsdm_priv* to_stm32_dfsdm_priv (struct stm32_dfsdm*) ; 

__attribute__((used)) static void stm32_dfsdm_clk_disable_unprepare(struct stm32_dfsdm *dfsdm)
{
	struct dfsdm_priv *priv = to_stm32_dfsdm_priv(dfsdm);

	if (priv->aclk)
		clk_disable_unprepare(priv->aclk);
	clk_disable_unprepare(priv->clk);
}