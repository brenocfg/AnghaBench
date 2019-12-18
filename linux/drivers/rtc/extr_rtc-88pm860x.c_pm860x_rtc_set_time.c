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
struct rtc_time {int tm_year; } ;
struct pm860x_rtc_info {int /*<<< orphan*/  (* sync ) (unsigned long) ;int /*<<< orphan*/  i2c; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PM8607_RTC_COUNTER1 ; 
 int /*<<< orphan*/  REG0_DATA ; 
 int /*<<< orphan*/  REG1_DATA ; 
 int /*<<< orphan*/  REG2_DATA ; 
 int /*<<< orphan*/  REG3_DATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 struct pm860x_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm860x_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  pm860x_page_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 

__attribute__((used)) static int pm860x_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct pm860x_rtc_info *info = dev_get_drvdata(dev);
	unsigned char buf[4];
	unsigned long ticks, base, data;

	if (tm->tm_year > 206) {
		dev_dbg(info->dev, "Set time %d out of range. "
			"Please set time between 1970 to 2106.\n",
			1900 + tm->tm_year);
		return -EINVAL;
	}
	rtc_tm_to_time(tm, &ticks);

	/* load 32-bit read-only counter */
	pm860x_bulk_read(info->i2c, PM8607_RTC_COUNTER1, 4, buf);
	data = ((unsigned long)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	base = ticks - data;
	dev_dbg(info->dev, "set base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	pm860x_page_reg_write(info->i2c, REG0_DATA, (base >> 24) & 0xFF);
	pm860x_page_reg_write(info->i2c, REG1_DATA, (base >> 16) & 0xFF);
	pm860x_page_reg_write(info->i2c, REG2_DATA, (base >> 8) & 0xFF);
	pm860x_page_reg_write(info->i2c, REG3_DATA, base & 0xFF);

	if (info->sync)
		info->sync(ticks);
	return 0;
}