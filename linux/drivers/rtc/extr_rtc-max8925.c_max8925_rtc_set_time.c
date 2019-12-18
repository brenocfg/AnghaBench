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
struct max8925_rtc_info {int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8925_RTC_SEC ; 
 int TIME_NUM ; 
 int data_calc (unsigned char*,struct rtc_time*,int) ; 
 struct max8925_rtc_info* dev_get_drvdata (struct device*) ; 
 int max8925_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 

__attribute__((used)) static int max8925_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct max8925_rtc_info *info = dev_get_drvdata(dev);
	unsigned char buf[TIME_NUM];
	int ret;

	ret = data_calc(buf, tm, TIME_NUM);
	if (ret < 0)
		goto out;
	ret = max8925_bulk_write(info->rtc, MAX8925_RTC_SEC, TIME_NUM, buf);
out:
	return ret;
}