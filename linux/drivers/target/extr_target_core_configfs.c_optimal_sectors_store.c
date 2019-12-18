#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct se_dev_attrib {scalar_t__ hw_max_sectors; TYPE_1__* da_dev; scalar_t__ optimal_sectors; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ export_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,TYPE_1__*,scalar_t__,...) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t optimal_sectors_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	u32 val;
	int ret;

	ret = kstrtou32(page, 0, &val);
	if (ret < 0)
		return ret;

	if (da->da_dev->export_count) {
		pr_err("dev[%p]: Unable to change SE Device"
			" optimal_sectors while export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		return -EINVAL;
	}
	if (val > da->hw_max_sectors) {
		pr_err("dev[%p]: Passed optimal_sectors %u cannot be"
			" greater than hw_max_sectors: %u\n",
			da->da_dev, val, da->hw_max_sectors);
		return -EINVAL;
	}

	da->optimal_sectors = val;
	pr_debug("dev[%p]: SE Device optimal_sectors changed to %u\n",
			da->da_dev, val);
	return count;
}