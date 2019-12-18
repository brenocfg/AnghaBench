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
struct mv64xxx_i2c_data {int /*<<< orphan*/  clk; int /*<<< orphan*/  reg_clk; int /*<<< orphan*/  rstc; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct mv64xxx_i2c_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv64xxx_i2c_remove(struct platform_device *dev)
{
	struct mv64xxx_i2c_data		*drv_data = platform_get_drvdata(dev);

	i2c_del_adapter(&drv_data->adapter);
	free_irq(drv_data->irq, drv_data);
	reset_control_assert(drv_data->rstc);
	clk_disable_unprepare(drv_data->reg_clk);
	clk_disable_unprepare(drv_data->clk);

	return 0;
}