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
struct rx6110_data {int /*<<< orphan*/  regmap; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RTC_NR_TIME ; 
 int /*<<< orphan*/  RX6110_BIT_CTRL_STOP ; 
 int /*<<< orphan*/  RX6110_BIT_FLAG_VLF ; 
 int /*<<< orphan*/  RX6110_REG_CTRL ; 
 int /*<<< orphan*/  RX6110_REG_FLAG ; 
 int /*<<< orphan*/  RX6110_REG_SEC ; 
 struct rx6110_data* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rx6110_rtc_tm_to_data (struct rtc_time*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rx6110_set_time(struct device *dev, struct rtc_time *tm)
{
	struct rx6110_data *rx6110 = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	int ret;

	ret = rx6110_rtc_tm_to_data(tm, data);
	if (ret < 0)
		return ret;

	/* set STOP bit before changing clock/calendar */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_CTRL,
				 RX6110_BIT_CTRL_STOP, RX6110_BIT_CTRL_STOP);
	if (ret)
		return ret;

	ret = regmap_bulk_write(rx6110->regmap, RX6110_REG_SEC, data,
				RTC_NR_TIME);
	if (ret)
		return ret;

	/* The time in the RTC is valid. Be sure to have VLF cleared. */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_FLAG,
				 RX6110_BIT_FLAG_VLF, 0);
	if (ret)
		return ret;

	/* clear STOP bit after changing clock/calendar */
	ret = regmap_update_bits(rx6110->regmap, RX6110_REG_CTRL,
				 RX6110_BIT_CTRL_STOP, 0);

	return ret;
}