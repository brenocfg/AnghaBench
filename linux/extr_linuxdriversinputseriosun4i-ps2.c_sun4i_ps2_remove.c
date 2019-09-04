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
struct sun4i_ps2data {int /*<<< orphan*/  reg_base; int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; int /*<<< orphan*/  serio; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sun4i_ps2data*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sun4i_ps2data*) ; 
 struct sun4i_ps2data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_ps2_remove(struct platform_device *pdev)
{
	struct sun4i_ps2data *drvdata = platform_get_drvdata(pdev);

	serio_unregister_port(drvdata->serio);

	free_irq(drvdata->irq, drvdata);

	clk_disable_unprepare(drvdata->clk);
	clk_put(drvdata->clk);

	iounmap(drvdata->reg_base);

	kfree(drvdata);

	return 0;
}