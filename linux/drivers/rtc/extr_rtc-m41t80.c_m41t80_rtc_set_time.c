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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; unsigned char tm_wday; } ;
struct m41t80_data {int features; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int M41T80_FEATURE_SQ_ALT ; 
 int M41T80_FLAGS_OF ; 
 size_t M41T80_REG_DAY ; 
 size_t M41T80_REG_FLAGS ; 
 size_t M41T80_REG_HOUR ; 
 size_t M41T80_REG_MIN ; 
 size_t M41T80_REG_MON ; 
 size_t M41T80_REG_SEC ; 
 size_t M41T80_REG_SSEC ; 
 size_t M41T80_REG_WDAY ; 
 size_t M41T80_REG_YEAR ; 
 unsigned char bin2bcd (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct m41t80_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,size_t) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,size_t,int) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,size_t,int,unsigned char*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int m41t80_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct m41t80_data *clientdata = i2c_get_clientdata(client);
	unsigned char buf[8];
	int err, flags;

	if (tm->tm_year < 100 || tm->tm_year > 199)
		return -EINVAL;

	buf[M41T80_REG_SSEC] = 0;
	buf[M41T80_REG_SEC] = bin2bcd(tm->tm_sec);
	buf[M41T80_REG_MIN] = bin2bcd(tm->tm_min);
	buf[M41T80_REG_HOUR] = bin2bcd(tm->tm_hour);
	buf[M41T80_REG_DAY] = bin2bcd(tm->tm_mday);
	buf[M41T80_REG_MON] = bin2bcd(tm->tm_mon + 1);
	buf[M41T80_REG_YEAR] = bin2bcd(tm->tm_year - 100);
	buf[M41T80_REG_WDAY] = tm->tm_wday;

	/* If the square wave output is controlled in the weekday register */
	if (clientdata->features & M41T80_FEATURE_SQ_ALT) {
		int val;

		val = i2c_smbus_read_byte_data(client, M41T80_REG_WDAY);
		if (val < 0)
			return val;

		buf[M41T80_REG_WDAY] |= (val & 0xf0);
	}

	err = i2c_smbus_write_i2c_block_data(client, M41T80_REG_SSEC,
					     sizeof(buf), buf);
	if (err < 0) {
		dev_err(&client->dev, "Unable to write to date registers\n");
		return err;
	}

	/* Clear the OF bit of Flags Register */
	flags = i2c_smbus_read_byte_data(client, M41T80_REG_FLAGS);
	if (flags < 0)
		return flags;

	err = i2c_smbus_write_byte_data(client, M41T80_REG_FLAGS,
					flags & ~M41T80_FLAGS_OF);
	if (err < 0) {
		dev_err(&client->dev, "Unable to write flags register\n");
		return err;
	}

	return err;
}