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
struct uniphier_i2c_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  adap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct uniphier_i2c_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int uniphier_i2c_remove(struct platform_device *pdev)
{
	struct uniphier_i2c_priv *priv = platform_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	clk_disable_unprepare(priv->clk);

	return 0;
}