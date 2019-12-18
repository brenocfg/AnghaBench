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
struct lpc18xx_wdt_dev {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct lpc18xx_wdt_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int lpc18xx_wdt_remove(struct platform_device *pdev)
{
	struct lpc18xx_wdt_dev *lpc18xx_wdt = platform_get_drvdata(pdev);

	dev_warn(&pdev->dev, "I quit now, hardware will probably reboot!\n");
	del_timer(&lpc18xx_wdt->timer);

	return 0;
}