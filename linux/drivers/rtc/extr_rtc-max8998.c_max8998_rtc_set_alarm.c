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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct max8998_rtc_info {scalar_t__ lp3974_bug_workaround; int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8998_ALARM0_SEC ; 
 struct max8998_rtc_info* dev_get_drvdata (struct device*) ; 
 int max8998_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int max8998_rtc_start_alarm (struct max8998_rtc_info*) ; 
 int max8998_rtc_stop_alarm (struct max8998_rtc_info*) ; 
 int /*<<< orphan*/  max8998_tm_to_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int max8998_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	int ret;

	max8998_tm_to_data(&alrm->time, data);

	ret = max8998_rtc_stop_alarm(info);
	if (ret < 0)
		return ret;

	ret = max8998_bulk_write(info->rtc, MAX8998_ALARM0_SEC, 8, data);
	if (ret < 0)
		return ret;

	if (info->lp3974_bug_workaround)
		msleep(2000);

	if (alrm->enabled)
		ret = max8998_rtc_start_alarm(info);

	return ret;
}