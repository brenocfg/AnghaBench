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
struct TYPE_2__ {struct omap_device* od; } ;
struct platform_device {int /*<<< orphan*/  dev; TYPE_1__ archdata; } ;
struct omap_hwmod {struct omap_device* od; } ;
struct omap_device {int hwmods_cnt; struct platform_device* pdev; struct omap_hwmod** hwmods; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct omap_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _add_hwmod_clocks_clkdev (struct omap_device*,struct omap_hwmod*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct omap_device*) ; 
 struct omap_hwmod** kmemdup (struct omap_hwmod**,int,int /*<<< orphan*/ ) ; 
 struct omap_device* kzalloc (int,int /*<<< orphan*/ ) ; 

struct omap_device *omap_device_alloc(struct platform_device *pdev,
					struct omap_hwmod **ohs, int oh_cnt)
{
	int ret = -ENOMEM;
	struct omap_device *od;
	int i;
	struct omap_hwmod **hwmods;

	od = kzalloc(sizeof(struct omap_device), GFP_KERNEL);
	if (!od) {
		ret = -ENOMEM;
		goto oda_exit1;
	}
	od->hwmods_cnt = oh_cnt;

	hwmods = kmemdup(ohs, sizeof(struct omap_hwmod *) * oh_cnt, GFP_KERNEL);
	if (!hwmods)
		goto oda_exit2;

	od->hwmods = hwmods;
	od->pdev = pdev;
	pdev->archdata.od = od;

	for (i = 0; i < oh_cnt; i++) {
		hwmods[i]->od = od;
		_add_hwmod_clocks_clkdev(od, hwmods[i]);
	}

	return od;

oda_exit2:
	kfree(od);
oda_exit1:
	dev_err(&pdev->dev, "omap_device: build failed (%d)\n", ret);

	return ERR_PTR(ret);
}