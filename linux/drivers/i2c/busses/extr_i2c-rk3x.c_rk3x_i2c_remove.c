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
struct rk3x_i2c {int /*<<< orphan*/  clk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  clk_rate_nb; int /*<<< orphan*/  adap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct rk3x_i2c* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rk3x_i2c_remove(struct platform_device *pdev)
{
	struct rk3x_i2c *i2c = platform_get_drvdata(pdev);

	i2c_del_adapter(&i2c->adap);

	clk_notifier_unregister(i2c->clk, &i2c->clk_rate_nb);
	clk_unprepare(i2c->pclk);
	clk_unprepare(i2c->clk);

	return 0;
}