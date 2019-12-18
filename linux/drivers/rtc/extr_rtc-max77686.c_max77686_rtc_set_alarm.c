#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct max77686_rtc_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* drv_data; int /*<<< orphan*/  rtc_regmap; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX77686_RTC_WRITE ; 
 size_t REG_ALARM1_SEC ; 
 int RTC_NR_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77686_rtc_info* dev_get_drvdata (struct device*) ; 
 int max77686_rtc_start_alarm (struct max77686_rtc_info*) ; 
 int max77686_rtc_stop_alarm (struct max77686_rtc_info*) ; 
 int max77686_rtc_tm_to_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct max77686_rtc_info*) ; 
 int max77686_rtc_update (struct max77686_rtc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77686_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	int ret;

	ret = max77686_rtc_tm_to_data(&alrm->time, data, info);
	if (ret < 0)
		return ret;

	mutex_lock(&info->lock);

	ret = max77686_rtc_stop_alarm(info);
	if (ret < 0)
		goto out;

	ret = regmap_bulk_write(info->rtc_regmap,
				info->drv_data->map[REG_ALARM1_SEC],
				data, ARRAY_SIZE(data));

	if (ret < 0) {
		dev_err(info->dev, "Fail to write alarm reg(%d)\n", ret);
		goto out;
	}

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);
	if (ret < 0)
		goto out;

	if (alrm->enabled)
		ret = max77686_rtc_start_alarm(info);
out:
	mutex_unlock(&info->lock);
	return ret;
}