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
struct img_ir_priv {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_remove_hw (struct img_ir_priv*) ; 
 int /*<<< orphan*/  img_ir_remove_raw (struct img_ir_priv*) ; 
 struct img_ir_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int img_ir_remove(struct platform_device *pdev)
{
	struct img_ir_priv *priv = platform_get_drvdata(pdev);

	free_irq(priv->irq, priv);
	img_ir_remove_hw(priv);
	img_ir_remove_raw(priv);

	if (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);
	if (!IS_ERR(priv->sys_clk))
		clk_disable_unprepare(priv->sys_clk);
	return 0;
}