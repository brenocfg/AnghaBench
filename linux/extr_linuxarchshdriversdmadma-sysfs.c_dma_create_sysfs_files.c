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
struct dma_info {TYPE_1__* pdev; } ;
struct device {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * bus; int /*<<< orphan*/  id; } ;
struct dma_channel {int chan; int /*<<< orphan*/  vchan; struct device dev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_config ; 
 int /*<<< orphan*/  dev_attr_count ; 
 int /*<<< orphan*/  dev_attr_dev_id ; 
 int /*<<< orphan*/  dev_attr_flags ; 
 int /*<<< orphan*/  dev_attr_mode ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  dma_subsys ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 

int dma_create_sysfs_files(struct dma_channel *chan, struct dma_info *info)
{
	struct device *dev = &chan->dev;
	char name[16];
	int ret;

	dev->id  = chan->vchan;
	dev->bus = &dma_subsys;

	ret = device_register(dev);
	if (ret)
		return ret;

	ret |= device_create_file(dev, &dev_attr_dev_id);
	ret |= device_create_file(dev, &dev_attr_count);
	ret |= device_create_file(dev, &dev_attr_mode);
	ret |= device_create_file(dev, &dev_attr_flags);
	ret |= device_create_file(dev, &dev_attr_config);

	if (unlikely(ret)) {
		dev_err(&info->pdev->dev, "Failed creating attrs\n");
		return ret;
	}

	snprintf(name, sizeof(name), "dma%d", chan->chan);
	return sysfs_create_link(&info->pdev->dev.kobj, &dev->kobj, name);
}