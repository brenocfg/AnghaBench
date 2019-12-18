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
struct rtc_time {int tm_year; } ;
struct rtc_wkalrm {struct rtc_time time; } ;
struct device {int dummy; } ;
struct da9052_rtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int da9052_rtc_enable_alarm (struct da9052_rtc*,int) ; 
 int da9052_set_alarm (struct da9052_rtc*,struct rtc_time*) ; 
 struct da9052_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int da9052_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	int ret;
	struct rtc_time *tm = &alrm->time;
	struct da9052_rtc *rtc = dev_get_drvdata(dev);

	/* DA9052 only has 6 bits for year - to represent 2000-2063 */
	if ((tm->tm_year < 100) || (tm->tm_year > 163))
		return -EINVAL;

	ret = da9052_rtc_enable_alarm(rtc, 0);
	if (ret < 0)
		return ret;

	ret = da9052_set_alarm(rtc, tm);
	if (ret < 0)
		return ret;

	ret = da9052_rtc_enable_alarm(rtc, 1);
	return ret;
}