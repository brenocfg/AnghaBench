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
struct sirfsoc_i2c {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct platform_device {int dummy; } ;
struct i2c_adapter {struct sirfsoc_i2c* algo_data; } ;

/* Variables and functions */
 scalar_t__ SIRFSOC_I2C_CTRL ; 
 int /*<<< orphan*/  SIRFSOC_I2C_RESET ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_adapter*) ; 
 struct i2c_adapter* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int i2c_sirfsoc_remove(struct platform_device *pdev)
{
	struct i2c_adapter *adapter = platform_get_drvdata(pdev);
	struct sirfsoc_i2c *siic = adapter->algo_data;

	writel(SIRFSOC_I2C_RESET, siic->base + SIRFSOC_I2C_CTRL);
	i2c_del_adapter(adapter);
	clk_unprepare(siic->clk);
	clk_put(siic->clk);
	return 0;
}