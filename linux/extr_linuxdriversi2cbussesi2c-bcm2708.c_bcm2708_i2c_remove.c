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
struct bcm2708_i2c {int /*<<< orphan*/  clk; int /*<<< orphan*/  base; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2708_i2c*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bcm2708_i2c*) ; 
 struct bcm2708_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2708_i2c_remove(struct platform_device *pdev)
{
	struct bcm2708_i2c *bi = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	i2c_del_adapter(&bi->adapter);
	free_irq(bi->irq, bi);
	iounmap(bi->base);
	clk_disable_unprepare(bi->clk);
	clk_put(bi->clk);
	kfree(bi);

	return 0;
}