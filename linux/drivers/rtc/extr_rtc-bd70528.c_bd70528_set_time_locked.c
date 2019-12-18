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
struct rohm_regmap_dev {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct bd70528_rtc_data {int dummy; } ;
struct bd70528_rtc {struct rohm_regmap_dev* mfd; } ;
typedef  int /*<<< orphan*/  rtc_data ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_REG_RTC_START ; 
 int bd70528_disable_rtc_based_timers (struct bd70528_rtc*,int*) ; 
 int bd70528_re_enable_rtc_based_timers (struct bd70528_rtc*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct bd70528_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bd70528_rtc_data*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bd70528_rtc_data*,int) ; 
 int /*<<< orphan*/  tm2rtc (struct rtc_time*,struct bd70528_rtc_data*) ; 

__attribute__((used)) static int bd70528_set_time_locked(struct device *dev, struct rtc_time *t)
{
	int ret, tmpret, old_states;
	struct bd70528_rtc_data rtc_data;
	struct bd70528_rtc *r = dev_get_drvdata(dev);
	struct rohm_regmap_dev *bd70528 = r->mfd;

	ret = bd70528_disable_rtc_based_timers(r, &old_states);
	if (ret)
		return ret;

	tmpret = regmap_bulk_read(bd70528->regmap,
				  BD70528_REG_RTC_START, &rtc_data,
				  sizeof(rtc_data));
	if (tmpret) {
		dev_err(dev, "Failed to read RTC time registers\n");
		goto renable_out;
	}
	tm2rtc(t, &rtc_data);

	tmpret = regmap_bulk_write(bd70528->regmap,
				   BD70528_REG_RTC_START, &rtc_data,
				   sizeof(rtc_data));
	if (tmpret) {
		dev_err(dev, "Failed to set RTC time\n");
		goto renable_out;
	}

renable_out:
	ret = bd70528_re_enable_rtc_based_timers(r, old_states);
	if (tmpret)
		ret = tmpret;

	return ret;
}