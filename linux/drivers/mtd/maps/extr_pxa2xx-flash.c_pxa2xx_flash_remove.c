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
struct TYPE_2__ {scalar_t__ cached; scalar_t__ virt; } ;
struct pxa2xx_flash_info {TYPE_1__ map; int /*<<< orphan*/  mtd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct pxa2xx_flash_info*) ; 
 int /*<<< orphan*/  map_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ ) ; 
 struct pxa2xx_flash_info* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pxa2xx_flash_remove(struct platform_device *dev)
{
	struct pxa2xx_flash_info *info = platform_get_drvdata(dev);

	mtd_device_unregister(info->mtd);

	map_destroy(info->mtd);
	iounmap(info->map.virt);
	if (info->map.cached)
		iounmap(info->map.cached);
	kfree(info);
	return 0;
}