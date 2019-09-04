#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s3c24xx_i2c {int /*<<< orphan*/  pctrl; int /*<<< orphan*/  adap; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct s3c24xx_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_deregister_cpufreq (struct s3c24xx_i2c*) ; 
 int /*<<< orphan*/  s3c24xx_i2c_dt_gpio_free (struct s3c24xx_i2c*) ; 

__attribute__((used)) static int s3c24xx_i2c_remove(struct platform_device *pdev)
{
	struct s3c24xx_i2c *i2c = platform_get_drvdata(pdev);

	clk_unprepare(i2c->clk);

	pm_runtime_disable(&pdev->dev);

	s3c24xx_i2c_deregister_cpufreq(i2c);

	i2c_del_adapter(&i2c->adap);

	if (pdev->dev.of_node && IS_ERR(i2c->pctrl))
		s3c24xx_i2c_dt_gpio_free(i2c);

	return 0;
}