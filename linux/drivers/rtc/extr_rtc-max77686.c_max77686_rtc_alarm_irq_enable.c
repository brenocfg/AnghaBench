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
struct max77686_rtc_info {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct max77686_rtc_info* dev_get_drvdata (struct device*) ; 
 int max77686_rtc_start_alarm (struct max77686_rtc_info*) ; 
 int max77686_rtc_stop_alarm (struct max77686_rtc_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max77686_rtc_alarm_irq_enable(struct device *dev,
					 unsigned int enabled)
{
	struct max77686_rtc_info *info = dev_get_drvdata(dev);
	int ret;

	mutex_lock(&info->lock);
	if (enabled)
		ret = max77686_rtc_start_alarm(info);
	else
		ret = max77686_rtc_stop_alarm(info);
	mutex_unlock(&info->lock);

	return ret;
}