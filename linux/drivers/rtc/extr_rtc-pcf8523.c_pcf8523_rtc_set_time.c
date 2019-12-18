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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int /*<<< orphan*/  tm_wday; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_SECONDS ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int pcf8523_start_rtc (struct i2c_client*) ; 
 int pcf8523_stop_rtc (struct i2c_client*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf8523_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct i2c_msg msg;
	u8 regs[8];
	int err;

	/*
	 * The hardware can only store values between 0 and 99 in it's YEAR
	 * register (with 99 overflowing to 0 on increment).
	 * After 2100-02-28 we could start interpreting the year to be in the
	 * interval [2100, 2199], but there is no path to switch in a smooth way
	 * because the chip handles YEAR=0x00 (and the out-of-spec
	 * YEAR=0xa0) as a leap year, but 2100 isn't.
	 */
	if (tm->tm_year < 100 || tm->tm_year >= 200)
		return -EINVAL;

	err = pcf8523_stop_rtc(client);
	if (err < 0)
		return err;

	regs[0] = REG_SECONDS;
	/* This will purposely overwrite REG_SECONDS_OS */
	regs[1] = bin2bcd(tm->tm_sec);
	regs[2] = bin2bcd(tm->tm_min);
	regs[3] = bin2bcd(tm->tm_hour);
	regs[4] = bin2bcd(tm->tm_mday);
	regs[5] = tm->tm_wday;
	regs[6] = bin2bcd(tm->tm_mon + 1);
	regs[7] = bin2bcd(tm->tm_year - 100);

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = sizeof(regs);
	msg.buf = regs;

	err = i2c_transfer(client->adapter, &msg, 1);
	if (err < 0) {
		/*
		 * If the time cannot be set, restart the RTC anyway. Note
		 * that errors are ignored if the RTC cannot be started so
		 * that we have a chance to propagate the original error.
		 */
		pcf8523_start_rtc(client);
		return err;
	}

	return pcf8523_start_rtc(client);
}