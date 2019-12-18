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
struct se_device {TYPE_1__* transport; scalar_t__ export_count; } ;
struct se_dev_attrib {struct se_device* da_dev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* format_prot ) (struct se_device*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_device*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct se_device*) ; 
 int /*<<< orphan*/  target_dev_configured (struct se_device*) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t pi_prot_format_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	struct se_device *dev = da->da_dev;
	bool flag;
	int ret;

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;

	if (!flag)
		return count;

	if (!dev->transport->format_prot) {
		pr_err("DIF protection format not supported by backend %s\n",
		       dev->transport->name);
		return -ENOSYS;
	}
	if (!target_dev_configured(dev)) {
		pr_err("DIF protection format requires device to be configured\n");
		return -ENODEV;
	}
	if (dev->export_count) {
		pr_err("dev[%p]: Unable to format SE Device PROT type while"
		       " export_count is %d\n", dev, dev->export_count);
		return -EINVAL;
	}

	ret = dev->transport->format_prot(dev);
	if (ret)
		return ret;

	pr_debug("dev[%p]: SE Device Protection Format complete\n", dev);
	return count;
}