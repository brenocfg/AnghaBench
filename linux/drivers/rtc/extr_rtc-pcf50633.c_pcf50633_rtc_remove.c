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
struct pcf50633_rtc {int /*<<< orphan*/  pcf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF50633_IRQ_ALARM ; 
 int /*<<< orphan*/  pcf50633_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcf50633_rtc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pcf50633_rtc_remove(struct platform_device *pdev)
{
	struct pcf50633_rtc *rtc;

	rtc = platform_get_drvdata(pdev);
	pcf50633_free_irq(rtc->pcf, PCF50633_IRQ_ALARM);

	return 0;
}