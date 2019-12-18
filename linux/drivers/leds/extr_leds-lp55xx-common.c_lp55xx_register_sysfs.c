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
struct lp55xx_device_config {int /*<<< orphan*/ * dev_attr_group; int /*<<< orphan*/  firmware_cb; int /*<<< orphan*/  run_engine; } ;
struct lp55xx_chip {struct lp55xx_device_config* cfg; TYPE_1__* cl; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lp55xx_engine_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lp55xx_register_sysfs(struct lp55xx_chip *chip)
{
	struct device *dev = &chip->cl->dev;
	struct lp55xx_device_config *cfg = chip->cfg;
	int ret;

	if (!cfg->run_engine || !cfg->firmware_cb)
		goto dev_specific_attrs;

	ret = sysfs_create_group(&dev->kobj, &lp55xx_engine_attr_group);
	if (ret)
		return ret;

dev_specific_attrs:
	return cfg->dev_attr_group ?
		sysfs_create_group(&dev->kobj, cfg->dev_attr_group) : 0;
}