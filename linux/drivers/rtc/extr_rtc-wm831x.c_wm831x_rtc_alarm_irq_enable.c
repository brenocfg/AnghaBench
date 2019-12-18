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
struct wm831x_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct wm831x_rtc* dev_get_drvdata (struct device*) ; 
 int wm831x_rtc_start_alarm (struct wm831x_rtc*) ; 
 int wm831x_rtc_stop_alarm (struct wm831x_rtc*) ; 

__attribute__((used)) static int wm831x_rtc_alarm_irq_enable(struct device *dev,
				       unsigned int enabled)
{
	struct wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);

	if (enabled)
		return wm831x_rtc_start_alarm(wm831x_rtc);
	else
		return wm831x_rtc_stop_alarm(wm831x_rtc);
}