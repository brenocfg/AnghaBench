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
typedef  int /*<<< orphan*/  year ;
struct rtc_time {int tm_year; } ;
struct rtc_mem {int nr; unsigned char* data; int /*<<< orphan*/  loc; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMOS_CHECKSUM ; 
 int /*<<< orphan*/  CMOS_YEAR ; 
 int pcf8583_read_mem (struct i2c_client*,struct rtc_mem*) ; 
 int pcf8583_set_datetime (struct i2c_client*,struct rtc_time*,int) ; 
 int pcf8583_write_mem (struct i2c_client*,struct rtc_mem*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf8583_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned char year[2], chk;
	struct rtc_mem cmos_year  = {
		.loc = CMOS_YEAR,
		.nr = sizeof(year),
		.data = year
	};
	struct rtc_mem cmos_check = {
		.loc = CMOS_CHECKSUM,
		.nr = 1,
		.data = &chk
	};
	unsigned int proper_year = tm->tm_year + 1900;
	int ret;

	/*
	 * The RTC's own 2-bit year must reflect the least
	 * significant two bits of the CMOS year.
	 */

	ret = pcf8583_set_datetime(client, tm, 1);
	if (ret)
		return ret;

	ret = pcf8583_read_mem(client, &cmos_check);
	if (ret)
		return ret;

	ret = pcf8583_read_mem(client, &cmos_year);
	if (ret)
		return ret;

	chk -= year[1] + year[0];

	year[1] = proper_year / 100;
	year[0] = proper_year % 100;

	chk += year[1] + year[0];

	ret = pcf8583_write_mem(client, &cmos_year);

	if (ret)
		return ret;

	ret = pcf8583_write_mem(client, &cmos_check);

	return ret;
}