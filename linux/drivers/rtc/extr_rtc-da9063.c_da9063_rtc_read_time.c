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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct da9063_compatible_rtc_regmap {int rtc_ready_to_read_mask; int /*<<< orphan*/  rtc_count_secs_reg; } ;
struct da9063_compatible_rtc {int rtc_sync; struct rtc_time alarm_time; int /*<<< orphan*/  regmap; struct da9063_compatible_rtc_regmap* config; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTC_DATA_LEN ; 
 size_t RTC_SEC ; 
 int /*<<< orphan*/  da9063_data_to_tm (int*,struct rtc_time*,struct da9063_compatible_rtc*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct da9063_compatible_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (struct rtc_time*,struct rtc_time*,int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 unsigned long rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int da9063_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	const struct da9063_compatible_rtc_regmap *config = rtc->config;
	unsigned long tm_secs;
	unsigned long al_secs;
	u8 data[RTC_DATA_LEN];
	int ret;

	ret = regmap_bulk_read(rtc->regmap,
			       config->rtc_count_secs_reg,
			       data, RTC_DATA_LEN);
	if (ret < 0) {
		dev_err(dev, "Failed to read RTC time data: %d\n", ret);
		return ret;
	}

	if (!(data[RTC_SEC] & config->rtc_ready_to_read_mask)) {
		dev_dbg(dev, "RTC not yet ready to be read by the host\n");
		return -EINVAL;
	}

	da9063_data_to_tm(data, tm, rtc);

	tm_secs = rtc_tm_to_time64(tm);
	al_secs = rtc_tm_to_time64(&rtc->alarm_time);

	/* handle the rtc synchronisation delay */
	if (rtc->rtc_sync == true && al_secs - tm_secs == 1)
		memcpy(tm, &rtc->alarm_time, sizeof(struct rtc_time));
	else
		rtc->rtc_sync = false;

	return 0;
}