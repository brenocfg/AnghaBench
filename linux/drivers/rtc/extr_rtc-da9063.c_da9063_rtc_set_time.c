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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct da9063_compatible_rtc_regmap {int /*<<< orphan*/  rtc_count_secs_reg; } ;
struct da9063_compatible_rtc {int /*<<< orphan*/  regmap; struct da9063_compatible_rtc_regmap* config; } ;

/* Variables and functions */
 int RTC_DATA_LEN ; 
 int /*<<< orphan*/  da9063_tm_to_data (struct rtc_time*,int /*<<< orphan*/ *,struct da9063_compatible_rtc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct da9063_compatible_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int da9063_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	const struct da9063_compatible_rtc_regmap *config = rtc->config;
	u8 data[RTC_DATA_LEN];
	int ret;

	da9063_tm_to_data(tm, data, rtc);
	ret = regmap_bulk_write(rtc->regmap,
				config->rtc_count_secs_reg,
				data, RTC_DATA_LEN);
	if (ret < 0)
		dev_err(dev, "Failed to set RTC time data: %d\n", ret);

	return ret;
}