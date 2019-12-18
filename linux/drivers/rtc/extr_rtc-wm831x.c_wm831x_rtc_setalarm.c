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
struct wm831x_rtc {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_RTC_ALARM_1 ; 
 int /*<<< orphan*/  WM831X_RTC_ALARM_2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct wm831x_rtc* dev_get_drvdata (struct device*) ; 
 unsigned long rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int wm831x_reg_write (struct wm831x*,int /*<<< orphan*/ ,unsigned long) ; 
 int wm831x_rtc_start_alarm (struct wm831x_rtc*) ; 
 int wm831x_rtc_stop_alarm (struct wm831x_rtc*) ; 

__attribute__((used)) static int wm831x_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	struct wm831x *wm831x = wm831x_rtc->wm831x;
	int ret;
	unsigned long time;

	time = rtc_tm_to_time64(&alrm->time);

	ret = wm831x_rtc_stop_alarm(wm831x_rtc);
	if (ret < 0) {
		dev_err(dev, "Failed to stop alarm: %d\n", ret);
		return ret;
	}

	ret = wm831x_reg_write(wm831x, WM831X_RTC_ALARM_1,
			       (time >> 16) & 0xffff);
	if (ret < 0) {
		dev_err(dev, "Failed to write ALARM_1: %d\n", ret);
		return ret;
	}

	ret = wm831x_reg_write(wm831x, WM831X_RTC_ALARM_2, time & 0xffff);
	if (ret < 0) {
		dev_err(dev, "Failed to write ALARM_2: %d\n", ret);
		return ret;
	}

	if (alrm->enabled) {
		ret = wm831x_rtc_start_alarm(wm831x_rtc);
		if (ret < 0) {
			dev_err(dev, "Failed to start alarm: %d\n", ret);
			return ret;
		}
	}

	return 0;
}