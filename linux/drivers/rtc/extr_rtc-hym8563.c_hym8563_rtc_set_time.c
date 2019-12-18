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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_wday; int tm_mon; } ;
struct i2c_client {int dummy; } ;
struct hym8563 {int valid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HYM8563_CTL1 ; 
 int /*<<< orphan*/  HYM8563_CTL1_STOP ; 
 int /*<<< orphan*/  HYM8563_SEC ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 struct hym8563* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int hym8563_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct hym8563 *hym8563 = i2c_get_clientdata(client);
	u8 buf[7];
	int ret;

	/* Years >= 2100 are to far in the future, 19XX is to early */
	if (tm->tm_year < 100 || tm->tm_year >= 200)
		return -EINVAL;

	buf[0] = bin2bcd(tm->tm_sec);
	buf[1] = bin2bcd(tm->tm_min);
	buf[2] = bin2bcd(tm->tm_hour);
	buf[3] = bin2bcd(tm->tm_mday);
	buf[4] = bin2bcd(tm->tm_wday);
	buf[5] = bin2bcd(tm->tm_mon + 1);

	/*
	 * While the HYM8563 has a century flag in the month register,
	 * it does not seem to carry it over a subsequent write/read.
	 * So we'll limit ourself to 100 years, starting at 2000 for now.
	 */
	buf[6] = bin2bcd(tm->tm_year - 100);

	/*
	 * CTL1 only contains TEST-mode bits apart from stop,
	 * so no need to read the value first
	 */
	ret = i2c_smbus_write_byte_data(client, HYM8563_CTL1,
						HYM8563_CTL1_STOP);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_i2c_block_data(client, HYM8563_SEC, 7, buf);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, HYM8563_CTL1, 0);
	if (ret < 0)
		return ret;

	hym8563->valid = true;

	return 0;
}