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
struct efm32_i2c_ddata {int /*<<< orphan*/  clk; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct efm32_i2c_ddata*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct efm32_i2c_ddata* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int efm32_i2c_remove(struct platform_device *pdev)
{
	struct efm32_i2c_ddata *ddata = platform_get_drvdata(pdev);

	i2c_del_adapter(&ddata->adapter);
	free_irq(ddata->irq, ddata);
	clk_disable_unprepare(ddata->clk);

	return 0;
}