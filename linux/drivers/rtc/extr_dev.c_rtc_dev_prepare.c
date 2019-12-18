#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  devt; } ;
struct rtc_device {scalar_t__ id; int /*<<< orphan*/  owner; TYPE_2__ char_dev; int /*<<< orphan*/  uie_timer; int /*<<< orphan*/  uie_task; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RTC_DEV_MAX ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rtc_dev_fops ; 
 int /*<<< orphan*/  rtc_devt ; 
 int /*<<< orphan*/  rtc_uie_task ; 
 int /*<<< orphan*/  rtc_uie_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtc_dev_prepare(struct rtc_device *rtc)
{
	if (!rtc_devt)
		return;

	if (rtc->id >= RTC_DEV_MAX) {
		dev_dbg(&rtc->dev, "too many RTC devices\n");
		return;
	}

	rtc->dev.devt = MKDEV(MAJOR(rtc_devt), rtc->id);

#ifdef CONFIG_RTC_INTF_DEV_UIE_EMUL
	INIT_WORK(&rtc->uie_task, rtc_uie_task);
	timer_setup(&rtc->uie_timer, rtc_uie_timer, 0);
#endif

	cdev_init(&rtc->char_dev, &rtc_dev_fops);
	rtc->char_dev.owner = rtc->owner;
}