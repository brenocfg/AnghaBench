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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {struct resource* resource; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct onenand_info {TYPE_1__ onenand; int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct onenand_info*) ; 
 int /*<<< orphan*/  onenand_release (int /*<<< orphan*/ *) ; 
 struct onenand_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long resource_size (struct resource*) ; 

__attribute__((used)) static int generic_onenand_remove(struct platform_device *pdev)
{
	struct onenand_info *info = platform_get_drvdata(pdev);
	struct resource *res = pdev->resource;
	unsigned long size = resource_size(res);

	if (info) {
		onenand_release(&info->mtd);
		release_mem_region(res->start, size);
		iounmap(info->onenand.base);
		kfree(info);
	}

	return 0;
}