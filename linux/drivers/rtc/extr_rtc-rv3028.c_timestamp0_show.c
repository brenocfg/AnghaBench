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
struct rv3028_data {int /*<<< orphan*/  regmap; } ;
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  RV3028_TS_COUNT ; 
 int /*<<< orphan*/  RV3028_TS_SEC ; 
 void* bcd2bin (int /*<<< orphan*/ ) ; 
 struct rv3028_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t timestamp0_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct rv3028_data *rv3028 = dev_get_drvdata(dev->parent);
	struct rtc_time tm;
	int ret, count;
	u8 date[6];

	ret = regmap_read(rv3028->regmap, RV3028_TS_COUNT, &count);
	if (ret)
		return ret;

	if (!count)
		return 0;

	ret = regmap_bulk_read(rv3028->regmap, RV3028_TS_SEC, date,
			       sizeof(date));
	if (ret)
		return ret;

	tm.tm_sec = bcd2bin(date[0]);
	tm.tm_min = bcd2bin(date[1]);
	tm.tm_hour = bcd2bin(date[2]);
	tm.tm_mday = bcd2bin(date[3]);
	tm.tm_mon = bcd2bin(date[4]) - 1;
	tm.tm_year = bcd2bin(date[5]) + 100;

	ret = rtc_valid_tm(&tm);
	if (ret)
		return ret;

	return sprintf(buf, "%llu\n",
		       (unsigned long long)rtc_tm_to_time64(&tm));
}