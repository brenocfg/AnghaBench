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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cdns_i2c {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_rate_change_nb; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct cdns_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns_i2c_remove(struct platform_device *pdev)
{
	struct cdns_i2c *id = platform_get_drvdata(pdev);

	i2c_del_adapter(&id->adap);
	clk_notifier_unregister(id->clk, &id->clk_rate_change_nb);
	clk_disable_unprepare(id->clk);
	pm_runtime_disable(&pdev->dev);

	return 0;
}