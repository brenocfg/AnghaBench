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
struct platform_device {int dummy; } ;
struct lpc18xx_gpio_chip {int /*<<< orphan*/  clk; TYPE_1__* pin_ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct lpc18xx_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int lpc18xx_gpio_remove(struct platform_device *pdev)
{
	struct lpc18xx_gpio_chip *gc = platform_get_drvdata(pdev);

	if (gc->pin_ic)
		irq_domain_remove(gc->pin_ic->domain);

	clk_disable_unprepare(gc->clk);

	return 0;
}