#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; struct resource* resource; } ;
struct onenand_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/ * parts; int /*<<< orphan*/ * mmcontrol; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; int /*<<< orphan*/  irq; int /*<<< orphan*/ * mmcontrol; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {TYPE_2__* priv; TYPE_1__ dev; } ;
struct onenand_info {TYPE_2__ onenand; TYPE_3__ mtd; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct onenand_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct onenand_info*) ; 
 struct onenand_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ onenand_scan (TYPE_3__*,int) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct onenand_info*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long resource_size (struct resource*) ; 

__attribute__((used)) static int generic_onenand_probe(struct platform_device *pdev)
{
	struct onenand_info *info;
	struct onenand_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct resource *res = pdev->resource;
	unsigned long size = resource_size(res);
	int err;

	info = kzalloc(sizeof(struct onenand_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if (!request_mem_region(res->start, size, dev_name(&pdev->dev))) {
		err = -EBUSY;
		goto out_free_info;
	}

	info->onenand.base = ioremap(res->start, size);
	if (!info->onenand.base) {
		err = -ENOMEM;
		goto out_release_mem_region;
	}

	info->onenand.mmcontrol = pdata ? pdata->mmcontrol : NULL;
	info->onenand.irq = platform_get_irq(pdev, 0);

	info->mtd.dev.parent = &pdev->dev;
	info->mtd.priv = &info->onenand;

	if (onenand_scan(&info->mtd, 1)) {
		err = -ENXIO;
		goto out_iounmap;
	}

	err = mtd_device_register(&info->mtd, pdata ? pdata->parts : NULL,
				  pdata ? pdata->nr_parts : 0);

	platform_set_drvdata(pdev, info);

	return 0;

out_iounmap:
	iounmap(info->onenand.base);
out_release_mem_region:
	release_mem_region(res->start, size);
out_free_info:
	kfree(info);

	return err;
}