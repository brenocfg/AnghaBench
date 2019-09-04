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
struct physmap_flash_info {int /*<<< orphan*/ ** mtd; int /*<<< orphan*/ * cmtd; } ;
struct physmap_flash_data {int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;

/* Variables and functions */
 int MAX_RESOURCES ; 
 struct physmap_flash_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_concat_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct physmap_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 

__attribute__((used)) static int physmap_flash_remove(struct platform_device *dev)
{
	struct physmap_flash_info *info;
	struct physmap_flash_data *physmap_data;
	int i;

	info = platform_get_drvdata(dev);
	if (info == NULL)
		return 0;

	physmap_data = dev_get_platdata(&dev->dev);

	if (info->cmtd) {
		mtd_device_unregister(info->cmtd);
		if (info->cmtd != info->mtd[0])
			mtd_concat_destroy(info->cmtd);
	}

	for (i = 0; i < MAX_RESOURCES; i++) {
		if (info->mtd[i] != NULL)
			map_destroy(info->mtd[i]);
	}

	if (physmap_data->exit)
		physmap_data->exit(dev);

	return 0;
}