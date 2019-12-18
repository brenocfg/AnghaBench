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

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tegra_rtc_alarm_irq_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_rtc_shutdown(struct platform_device *pdev)
{
	dev_vdbg(&pdev->dev, "disabling interrupts\n");
	tegra_rtc_alarm_irq_enable(&pdev->dev, 0);
}