#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  model; } ;
struct se_device {TYPE_2__* transport; TYPE_1__ t10_wwn; scalar_t__ export_count; } ;
struct se_dev_attrib {int emulate_model_alias; struct se_device* da_dev; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  inquiry_prod; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int INQUIRY_MODEL_LEN ; 
 int /*<<< orphan*/  dev_set_t10_wwn_model_alias (struct se_device*) ; 
 int /*<<< orphan*/  pr_err (char*,struct se_device*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strtobool (char const*,int*) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t emulate_model_alias_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	struct se_device *dev = da->da_dev;
	bool flag;
	int ret;

	if (dev->export_count) {
		pr_err("dev[%p]: Unable to change model alias"
			" while export_count is %d\n",
			dev, dev->export_count);
		return -EINVAL;
	}

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;

	BUILD_BUG_ON(sizeof(dev->t10_wwn.model) != INQUIRY_MODEL_LEN + 1);
	if (flag) {
		dev_set_t10_wwn_model_alias(dev);
	} else {
		strlcpy(dev->t10_wwn.model, dev->transport->inquiry_prod,
			sizeof(dev->t10_wwn.model));
	}
	da->emulate_model_alias = flag;
	return count;
}