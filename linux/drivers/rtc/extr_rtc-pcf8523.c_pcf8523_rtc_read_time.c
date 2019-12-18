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
struct rtc_time {int tm_wday; void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int EINVAL ; 
 scalar_t__ I2C_M_RD ; 
 int REG_SECONDS ; 
 int REG_SECONDS_OS ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 
 int pcf8523_voltage_low (struct i2c_client*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf8523_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 start = REG_SECONDS, regs[7];
	struct i2c_msg msgs[2];
	int err;

	err = pcf8523_voltage_low(client);
	if (err < 0) {
		return err;
	} else if (err > 0) {
		dev_err(dev, "low voltage detected, time is unreliable\n");
		return -EINVAL;
	}

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &start;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = sizeof(regs);
	msgs[1].buf = regs;

	err = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (err < 0)
		return err;

	if (regs[0] & REG_SECONDS_OS)
		return -EINVAL;

	tm->tm_sec = bcd2bin(regs[0] & 0x7f);
	tm->tm_min = bcd2bin(regs[1] & 0x7f);
	tm->tm_hour = bcd2bin(regs[2] & 0x3f);
	tm->tm_mday = bcd2bin(regs[3] & 0x3f);
	tm->tm_wday = regs[4] & 0x7;
	tm->tm_mon = bcd2bin(regs[5] & 0x1f) - 1;
	tm->tm_year = bcd2bin(regs[6]) + 100;

	return 0;
}