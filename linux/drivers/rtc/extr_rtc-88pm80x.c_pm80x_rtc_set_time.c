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
struct rtc_time {int dummy; } ;
struct pm80x_rtc_info {int /*<<< orphan*/  map; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM800_RTC_COUNTER1 ; 
 int /*<<< orphan*/  PM800_RTC_EXPIRE2_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long) ; 
 struct pm80x_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned long rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int pm80x_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct pm80x_rtc_info *info = dev_get_drvdata(dev);
	unsigned char buf[4];
	unsigned long ticks, base, data;

	ticks = rtc_tm_to_time64(tm);

	/* load 32-bit read-only counter */
	regmap_raw_read(info->map, PM800_RTC_COUNTER1, buf, 4);
	data = ((unsigned long)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	base = ticks - data;
	dev_dbg(info->dev, "set base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);
	buf[0] = base & 0xFF;
	buf[1] = (base >> 8) & 0xFF;
	buf[2] = (base >> 16) & 0xFF;
	buf[3] = (base >> 24) & 0xFF;
	regmap_raw_write(info->map, PM800_RTC_EXPIRE2_1, buf, 4);

	return 0;
}