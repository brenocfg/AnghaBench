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
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct pm80x_rtc_info {int /*<<< orphan*/  map; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int PM800_ALARM ; 
 int PM800_ALARM1_EN ; 
 int PM800_ALARM_WAKEUP ; 
 int /*<<< orphan*/  PM800_RTC_CONTROL ; 
 int /*<<< orphan*/  PM800_RTC_EXPIRE1_1 ; 
 int /*<<< orphan*/  PM800_RTC_EXPIRE2_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long,...) ; 
 struct pm80x_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_raw_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm80x_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct pm80x_rtc_info *info = dev_get_drvdata(dev);
	unsigned char buf[4];
	unsigned long ticks, base, data;
	int ret;

	regmap_raw_read(info->map, PM800_RTC_EXPIRE2_1, buf, 4);
	base = ((unsigned long)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	regmap_raw_read(info->map, PM800_RTC_EXPIRE1_1, buf, 4);
	data = ((unsigned long)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%lx, RO count:0x%lx, ticks:0x%lx\n",
		base, data, ticks);

	rtc_time64_to_tm(ticks, &alrm->time);
	regmap_read(info->map, PM800_RTC_CONTROL, &ret);
	alrm->enabled = (ret & PM800_ALARM1_EN) ? 1 : 0;
	alrm->pending = (ret & (PM800_ALARM | PM800_ALARM_WAKEUP)) ? 1 : 0;
	return 0;
}