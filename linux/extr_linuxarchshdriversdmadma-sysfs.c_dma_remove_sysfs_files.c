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
struct dma_info {TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct dma_channel {int chan; struct device dev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_config ; 
 int /*<<< orphan*/  dev_attr_count ; 
 int /*<<< orphan*/  dev_attr_dev_id ; 
 int /*<<< orphan*/  dev_attr_flags ; 
 int /*<<< orphan*/  dev_attr_mode ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void dma_remove_sysfs_files(struct dma_channel *chan, struct dma_info *info)
{
	struct device *dev = &chan->dev;
	char name[16];

	device_remove_file(dev, &dev_attr_dev_id);
	device_remove_file(dev, &dev_attr_count);
	device_remove_file(dev, &dev_attr_mode);
	device_remove_file(dev, &dev_attr_flags);
	device_remove_file(dev, &dev_attr_config);

	snprintf(name, sizeof(name), "dma%d", chan->chan);
	sysfs_remove_link(&info->pdev->dev.kobj, name);

	device_unregister(dev);
}