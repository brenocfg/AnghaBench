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
struct rbtx4939_flash_info {scalar_t__ mtd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (scalar_t__) ; 
 struct rbtx4939_flash_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rbtx4939_flash_remove(struct platform_device *dev)
{
	struct rbtx4939_flash_info *info;

	info = platform_get_drvdata(dev);
	if (!info)
		return 0;

	if (info->mtd) {
		mtd_device_unregister(info->mtd);
		map_destroy(info->mtd);
	}
	return 0;
}