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
struct rtc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ops_lock; int /*<<< orphan*/ * ops; int /*<<< orphan*/  char_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_proc_del_device (struct rtc_device*) ; 

__attribute__((used)) static void rtc_device_unregister(struct rtc_device *rtc)
{
	mutex_lock(&rtc->ops_lock);
	/*
	 * Remove innards of this RTC, then disable it, before
	 * letting any rtc_class_open() users access it again
	 */
	rtc_proc_del_device(rtc);
	cdev_device_del(&rtc->char_dev, &rtc->dev);
	rtc->ops = NULL;
	mutex_unlock(&rtc->ops_lock);
	put_device(&rtc->dev);
}