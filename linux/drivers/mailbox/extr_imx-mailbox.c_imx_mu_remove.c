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
struct imx_mu_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct imx_mu_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int imx_mu_remove(struct platform_device *pdev)
{
	struct imx_mu_priv *priv = platform_get_drvdata(pdev);

	clk_disable_unprepare(priv->clk);

	return 0;
}