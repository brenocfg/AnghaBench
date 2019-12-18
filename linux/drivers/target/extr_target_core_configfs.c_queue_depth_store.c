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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ queue_depth; scalar_t__ hw_queue_depth; } ;
struct se_device {scalar_t__ queue_depth; TYPE_1__ dev_attrib; scalar_t__ export_count; } ;
struct se_dev_attrib {scalar_t__ queue_depth; struct se_device* da_dev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_device*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,struct se_device*,...) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t queue_depth_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	struct se_device *dev = da->da_dev;
	u32 val;
	int ret;

	ret = kstrtou32(page, 0, &val);
	if (ret < 0)
		return ret;

	if (dev->export_count) {
		pr_err("dev[%p]: Unable to change SE Device TCQ while"
			" export_count is %d\n",
			dev, dev->export_count);
		return -EINVAL;
	}
	if (!val) {
		pr_err("dev[%p]: Illegal ZERO value for queue_depth\n", dev);
		return -EINVAL;
	}

	if (val > dev->dev_attrib.queue_depth) {
		if (val > dev->dev_attrib.hw_queue_depth) {
			pr_err("dev[%p]: Passed queue_depth:"
				" %u exceeds TCM/SE_Device MAX"
				" TCQ: %u\n", dev, val,
				dev->dev_attrib.hw_queue_depth);
			return -EINVAL;
		}
	}
	da->queue_depth = dev->queue_depth = val;
	pr_debug("dev[%p]: SE Device TCQ Depth changed to: %u\n", dev, val);
	return count;
}