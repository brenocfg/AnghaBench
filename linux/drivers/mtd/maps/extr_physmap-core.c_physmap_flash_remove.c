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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct physmap_flash_info {scalar_t__ cmtd; scalar_t__* mtds; int nmaps; } ;
struct physmap_flash_data {int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;

/* Variables and functions */
 struct physmap_flash_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_concat_destroy (scalar_t__) ; 
 int mtd_device_unregister (scalar_t__) ; 
 struct physmap_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

__attribute__((used)) static int physmap_flash_remove(struct platform_device *dev)
{
	struct physmap_flash_info *info;
	struct physmap_flash_data *physmap_data;
	int i, err;

	info = platform_get_drvdata(dev);
	if (!info)
		return 0;

	if (info->cmtd) {
		err = mtd_device_unregister(info->cmtd);
		if (err)
			return err;

		if (info->cmtd != info->mtds[0])
			mtd_concat_destroy(info->cmtd);
	}

	for (i = 0; i < info->nmaps; i++) {
		if (info->mtds[i])
			map_destroy(info->mtds[i]);
	}

	physmap_data = dev_get_platdata(&dev->dev);
	if (physmap_data && physmap_data->exit)
		physmap_data->exit(dev);

	return 0;
}