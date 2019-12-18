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
struct clk {int dummy; } ;
struct bcm2835_i2c_dev {int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  clk_rate_exclusive_put (struct clk*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2835_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct bcm2835_i2c_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm2835_i2c_remove(struct platform_device *pdev)
{
	struct bcm2835_i2c_dev *i2c_dev = platform_get_drvdata(pdev);
	struct clk *bus_clk = devm_clk_get(i2c_dev->dev, "div");

	clk_rate_exclusive_put(bus_clk);
	clk_disable_unprepare(bus_clk);

	free_irq(i2c_dev->irq, i2c_dev);
	i2c_del_adapter(&i2c_dev->adapter);

	return 0;
}