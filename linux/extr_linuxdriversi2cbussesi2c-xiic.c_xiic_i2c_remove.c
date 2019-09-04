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
struct xiic_i2c {int /*<<< orphan*/  clk; int /*<<< orphan*/  adap; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct xiic_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xiic_deinit (struct xiic_i2c*) ; 

__attribute__((used)) static int xiic_i2c_remove(struct platform_device *pdev)
{
	struct xiic_i2c *i2c = platform_get_drvdata(pdev);
	int ret;

	/* remove adapter & data */
	i2c_del_adapter(&i2c->adap);

	ret = clk_prepare_enable(i2c->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		return ret;
	}
	xiic_deinit(i2c);
	clk_disable_unprepare(i2c->clk);
	pm_runtime_disable(&pdev->dev);

	return 0;
}