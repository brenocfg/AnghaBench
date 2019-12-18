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
struct rtc_time {void* tm_year; void* tm_mon; void* tm_wday; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct hym8563 {int /*<<< orphan*/  valid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int HYM8563_DAY_MASK ; 
 int HYM8563_HOUR_MASK ; 
 int HYM8563_MIN_MASK ; 
 int HYM8563_MONTH_MASK ; 
 int /*<<< orphan*/  HYM8563_SEC ; 
 int HYM8563_SEC_MASK ; 
 int HYM8563_WEEKDAY_MASK ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct hym8563* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int hym8563_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct hym8563 *hym8563 = i2c_get_clientdata(client);
	u8 buf[7];
	int ret;

	if (!hym8563->valid) {
		dev_warn(&client->dev, "no valid clock/calendar values available\n");
		return -EPERM;
	}

	ret = i2c_smbus_read_i2c_block_data(client, HYM8563_SEC, 7, buf);
	if (ret < 0)
		return ret;

	tm->tm_sec = bcd2bin(buf[0] & HYM8563_SEC_MASK);
	tm->tm_min = bcd2bin(buf[1] & HYM8563_MIN_MASK);
	tm->tm_hour = bcd2bin(buf[2] & HYM8563_HOUR_MASK);
	tm->tm_mday = bcd2bin(buf[3] & HYM8563_DAY_MASK);
	tm->tm_wday = bcd2bin(buf[4] & HYM8563_WEEKDAY_MASK); /* 0 = Sun */
	tm->tm_mon = bcd2bin(buf[5] & HYM8563_MONTH_MASK) - 1; /* 0 = Jan */
	tm->tm_year = bcd2bin(buf[6]) + 100;

	return 0;
}