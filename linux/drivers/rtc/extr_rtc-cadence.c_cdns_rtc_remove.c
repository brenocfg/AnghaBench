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
struct cdns_rtc {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_rtc_alarm_irq_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cdns_rtc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cdns_rtc_remove(struct platform_device *pdev)
{
	struct cdns_rtc *crtc = platform_get_drvdata(pdev);

	cdns_rtc_alarm_irq_enable(&pdev->dev, 0);
	device_init_wakeup(&pdev->dev, 0);

	clk_disable_unprepare(crtc->pclk);
	clk_disable_unprepare(crtc->ref_clk);

	return 0;
}