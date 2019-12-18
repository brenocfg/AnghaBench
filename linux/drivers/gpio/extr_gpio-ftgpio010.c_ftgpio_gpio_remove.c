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
struct ftgpio_gpio {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ftgpio_gpio* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ftgpio_gpio_remove(struct platform_device *pdev)
{
	struct ftgpio_gpio *g = platform_get_drvdata(pdev);

	if (!IS_ERR(g->clk))
		clk_disable_unprepare(g->clk);
	return 0;
}