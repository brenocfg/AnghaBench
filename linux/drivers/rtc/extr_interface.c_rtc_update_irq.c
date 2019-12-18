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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {int /*<<< orphan*/  irqwork; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct rtc_device*) ; 
 int /*<<< orphan*/  pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void rtc_update_irq(struct rtc_device *rtc,
		    unsigned long num, unsigned long events)
{
	if (IS_ERR_OR_NULL(rtc))
		return;

	pm_stay_awake(rtc->dev.parent);
	schedule_work(&rtc->irqwork);
}