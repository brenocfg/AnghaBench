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
struct rtc_time {int dummy; } ;
struct max77686_rtc_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* drv_data; int /*<<< orphan*/  rtc_regmap; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX77686_RTC_READ ; 
 size_t REG_RTC_SEC ; 
 int RTC_NR_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77686_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  max77686_rtc_data_to_tm (int /*<<< orphan*/ *,struct rtc_time*,struct max77686_rtc_info*) ; 
 int max77686_rtc_update (struct max77686_rtc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77686_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	int ret;

	mutex_lock(&info->lock);

	ret = max77686_rtc_update(info, MAX77686_RTC_READ);
	if (ret < 0)
		goto out;

	ret = regmap_bulk_read(info->rtc_regmap,
			       info->drv_data->map[REG_RTC_SEC],
			       data, ARRAY_SIZE(data));
	if (ret < 0) {
		dev_err(info->dev, "Fail to read time reg(%d)\n", ret);
		goto out;
	}

	max77686_rtc_data_to_tm(data, tm, info);

out:
	mutex_unlock(&info->lock);
	return ret;
}