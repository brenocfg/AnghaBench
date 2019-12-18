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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct ds3232 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_SECONDS ; 
 int bin2bcd (int) ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ds3232_set_time(struct device *dev, struct rtc_time *time)
{
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	u8 buf[7];

	/* Extract time from rtc_time and load into ds3232*/

	buf[0] = bin2bcd(time->tm_sec);
	buf[1] = bin2bcd(time->tm_min);
	buf[2] = bin2bcd(time->tm_hour);
	/* Day of the week in linux range is 0~6 while 1~7 in RTC chip */
	buf[3] = bin2bcd(time->tm_wday + 1);
	buf[4] = bin2bcd(time->tm_mday); /* Date */
	/* linux tm_mon range:0~11, while month range is 1~12 in RTC chip */
	buf[5] = bin2bcd(time->tm_mon + 1);
	if (time->tm_year >= 100) {
		buf[5] |= 0x80;
		buf[6] = bin2bcd(time->tm_year - 100);
	} else {
		buf[6] = bin2bcd(time->tm_year);
	}

	return regmap_bulk_write(ds3232->regmap, DS3232_REG_SECONDS, buf, 7);
}