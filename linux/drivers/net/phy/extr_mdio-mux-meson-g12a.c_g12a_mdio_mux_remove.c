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
struct platform_device {int dummy; } ;
struct g12a_mdio_mux {int /*<<< orphan*/  pclk; int /*<<< orphan*/  pll; scalar_t__ pll_is_enabled; int /*<<< orphan*/  mux_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_mux_uninit (int /*<<< orphan*/ ) ; 
 struct g12a_mdio_mux* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int g12a_mdio_mux_remove(struct platform_device *pdev)
{
	struct g12a_mdio_mux *priv = platform_get_drvdata(pdev);

	mdio_mux_uninit(priv->mux_handle);

	if (priv->pll_is_enabled)
		clk_disable_unprepare(priv->pll);

	clk_disable_unprepare(priv->pclk);

	return 0;
}