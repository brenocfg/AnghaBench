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
struct lpc18xx_gpio_chip {int /*<<< orphan*/  clk; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct lpc18xx_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int lpc18xx_gpio_remove(struct platform_device *pdev)
{
	struct lpc18xx_gpio_chip *gc = platform_get_drvdata(pdev);

	gpiochip_remove(&gc->gpio);
	clk_disable_unprepare(gc->clk);

	return 0;
}