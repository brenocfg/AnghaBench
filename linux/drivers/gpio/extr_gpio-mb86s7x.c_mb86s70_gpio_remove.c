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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mb86s70_gpio_chip {int /*<<< orphan*/  clk; int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_gpiochip_free_interrupts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ *) ; 
 struct mb86s70_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mb86s70_gpio_remove(struct platform_device *pdev)
{
	struct mb86s70_gpio_chip *gchip = platform_get_drvdata(pdev);

	if (has_acpi_companion(&pdev->dev))
		acpi_gpiochip_free_interrupts(&gchip->gc);
	gpiochip_remove(&gchip->gc);
	clk_disable_unprepare(gchip->clk);

	return 0;
}