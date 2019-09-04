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
struct ixp4xx_flash_info {scalar_t__ mtd; } ;
struct flash_platform_data {int /*<<< orphan*/  (* exit ) () ;} ;

/* Variables and functions */
 struct flash_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (scalar_t__) ; 
 struct ixp4xx_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int ixp4xx_flash_remove(struct platform_device *dev)
{
	struct flash_platform_data *plat = dev_get_platdata(&dev->dev);
	struct ixp4xx_flash_info *info = platform_get_drvdata(dev);

	if(!info)
		return 0;

	if (info->mtd) {
		mtd_device_unregister(info->mtd);
		map_destroy(info->mtd);
	}

	if (plat->exit)
		plat->exit();

	return 0;
}