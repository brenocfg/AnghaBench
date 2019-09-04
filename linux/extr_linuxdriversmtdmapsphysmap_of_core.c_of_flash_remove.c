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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_flash {scalar_t__ cmtd; int list_size; TYPE_2__* list; } ;
struct TYPE_3__ {scalar_t__ virt; } ;
struct TYPE_4__ {scalar_t__ mtd; scalar_t__ res; TYPE_1__ map; } ;

/* Variables and functions */
 struct of_flash* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_concat_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  release_resource (scalar_t__) ; 

__attribute__((used)) static int of_flash_remove(struct platform_device *dev)
{
	struct of_flash *info;
	int i;

	info = dev_get_drvdata(&dev->dev);
	if (!info)
		return 0;
	dev_set_drvdata(&dev->dev, NULL);

	if (info->cmtd) {
		mtd_device_unregister(info->cmtd);
		if (info->cmtd != info->list[0].mtd)
			mtd_concat_destroy(info->cmtd);
	}

	for (i = 0; i < info->list_size; i++) {
		if (info->list[i].mtd)
			map_destroy(info->list[i].mtd);

		if (info->list[i].map.virt)
			iounmap(info->list[i].map.virt);

		if (info->list[i].res) {
			release_resource(info->list[i].res);
			kfree(info->list[i].res);
		}
	}
	return 0;
}