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
struct tps65910 {int /*<<< orphan*/  regmap; } ;
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int NUM_TIME_REGS ; 
 int /*<<< orphan*/  TPS65910_RTC_CTRL ; 
 int /*<<< orphan*/  TPS65910_RTC_CTRL_GET_TIME ; 
 int /*<<< orphan*/  TPS65910_SECONDS ; 
 void* bcd2bin (unsigned char) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	unsigned char rtc_data[NUM_TIME_REGS];
	struct tps65910 *tps = dev_get_drvdata(dev->parent);
	int ret;

	/* Copy RTC counting registers to static registers or latches */
	ret = regmap_update_bits(tps->regmap, TPS65910_RTC_CTRL,
		TPS65910_RTC_CTRL_GET_TIME, TPS65910_RTC_CTRL_GET_TIME);
	if (ret < 0) {
		dev_err(dev, "RTC CTRL reg update failed with err:%d\n", ret);
		return ret;
	}

	ret = regmap_bulk_read(tps->regmap, TPS65910_SECONDS, rtc_data,
		NUM_TIME_REGS);
	if (ret < 0) {
		dev_err(dev, "reading from RTC failed with err:%d\n", ret);
		return ret;
	}

	tm->tm_sec = bcd2bin(rtc_data[0]);
	tm->tm_min = bcd2bin(rtc_data[1]);
	tm->tm_hour = bcd2bin(rtc_data[2]);
	tm->tm_mday = bcd2bin(rtc_data[3]);
	tm->tm_mon = bcd2bin(rtc_data[4]) - 1;
	tm->tm_year = bcd2bin(rtc_data[5]) + 100;

	return ret;
}