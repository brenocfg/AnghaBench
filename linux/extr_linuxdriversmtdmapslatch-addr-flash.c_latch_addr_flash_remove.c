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
struct TYPE_3__ {int /*<<< orphan*/ * virt; } ;
struct latch_addr_flash_info {TYPE_2__* res; TYPE_1__ map; int /*<<< orphan*/ * mtd; } ;
struct latch_addr_flash_data {int /*<<< orphan*/  data; int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 struct latch_addr_flash_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct latch_addr_flash_info*) ; 
 int /*<<< orphan*/  map_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct latch_addr_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int latch_addr_flash_remove(struct platform_device *dev)
{
	struct latch_addr_flash_info *info;
	struct latch_addr_flash_data *latch_addr_data;

	info = platform_get_drvdata(dev);
	if (info == NULL)
		return 0;

	latch_addr_data = dev_get_platdata(&dev->dev);

	if (info->mtd != NULL) {
		mtd_device_unregister(info->mtd);
		map_destroy(info->mtd);
	}

	if (info->map.virt != NULL)
		iounmap(info->map.virt);

	if (info->res != NULL)
		release_mem_region(info->res->start, resource_size(info->res));

	kfree(info);

	if (latch_addr_data->done)
		latch_addr_data->done(latch_addr_data->data);

	return 0;
}