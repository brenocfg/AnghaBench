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
struct lpc32xx_rtc {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct lpc32xx_rtc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int lpc32xx_rtc_remove(struct platform_device *pdev)
{
	struct lpc32xx_rtc *rtc = platform_get_drvdata(pdev);

	if (rtc->irq >= 0)
		device_init_wakeup(&pdev->dev, 0);

	return 0;
}