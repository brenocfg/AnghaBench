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
struct tb_switch {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 size_t tb_switch_set_authorized (struct tb_switch*,unsigned int) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static ssize_t authorized_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct tb_switch *sw = tb_to_switch(dev);
	unsigned int val;
	ssize_t ret;

	ret = kstrtouint(buf, 0, &val);
	if (ret)
		return ret;
	if (val > 2)
		return -EINVAL;

	pm_runtime_get_sync(&sw->dev);
	ret = tb_switch_set_authorized(sw, val);
	pm_runtime_mark_last_busy(&sw->dev);
	pm_runtime_put_autosuspend(&sw->dev);

	return ret ? ret : count;
}