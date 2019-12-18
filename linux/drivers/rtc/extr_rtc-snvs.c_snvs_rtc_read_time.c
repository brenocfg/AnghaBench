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
struct snvs_rtc_data {int dummy; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct snvs_rtc_data* dev_get_drvdata (struct device*) ; 
 unsigned long rtc_read_lp_counter (struct snvs_rtc_data*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int snvs_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct snvs_rtc_data *data = dev_get_drvdata(dev);
	unsigned long time = rtc_read_lp_counter(data);

	rtc_time64_to_tm(time, tm);

	return 0;
}