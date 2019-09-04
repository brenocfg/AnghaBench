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
 int /*<<< orphan*/  brcmstb_gpio_quiesce (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void brcmstb_gpio_shutdown(struct platform_device *pdev)
{
	/* Enable GPIO for S5 cold boot */
	brcmstb_gpio_quiesce(&pdev->dev, false);
}