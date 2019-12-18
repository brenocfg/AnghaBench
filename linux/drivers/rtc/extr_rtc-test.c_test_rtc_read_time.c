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
struct rtc_time {int dummy; } ;
struct rtc_test_data {scalar_t__ offset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rtc_test_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 

__attribute__((used)) static int test_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct rtc_test_data *rtd = dev_get_drvdata(dev);

	rtc_time64_to_tm(ktime_get_real_seconds() + rtd->offset, tm);

	return 0;
}