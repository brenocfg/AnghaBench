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
struct rtc_wkalrm {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int imx_sc_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	/*
	 * SCU firmware does NOT provide read alarm API, but .read_alarm
	 * callback is required by RTC framework to support alarm function,
	 * so just return here.
	 */
	return 0;
}