#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct map_info {int bankwidth; int /*<<< orphan*/  copy_from; int /*<<< orphan*/  copy_to; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct device_node* device_node; int /*<<< orphan*/  name; int /*<<< orphan*/  virt; int /*<<< orphan*/  size; } ;
struct hyperbus_ops {int (* calibrate ) (struct hyperbus_device*) ;scalar_t__ copy_from; scalar_t__ copy_to; scalar_t__ write16; scalar_t__ read16; } ;
struct hyperbus_device {TYPE_2__* mtd; struct map_info map; int /*<<< orphan*/  memtype; struct hyperbus_ctlr* ctlr; struct device_node* np; } ;
struct hyperbus_ctlr {int calibrated; struct hyperbus_ops* ops; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device* parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  HYPERFLASH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 TYPE_2__* do_map_probe (char*,struct map_info*) ; 
 int /*<<< orphan*/  hyperbus_copy_from ; 
 int /*<<< orphan*/  hyperbus_copy_to ; 
 int /*<<< orphan*/  hyperbus_read16 ; 
 int /*<<< orphan*/  hyperbus_write16 ; 
 int /*<<< orphan*/  map_destroy (TYPE_2__*) ; 
 int mtd_device_register (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_of_node (TYPE_2__*,struct device_node*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  simple_map_init (struct map_info*) ; 
 int stub1 (struct hyperbus_device*) ; 

int hyperbus_register_device(struct hyperbus_device *hbdev)
{
	const struct hyperbus_ops *ops;
	struct hyperbus_ctlr *ctlr;
	struct device_node *np;
	struct map_info *map;
	struct resource res;
	struct device *dev;
	int ret;

	if (!hbdev || !hbdev->np || !hbdev->ctlr || !hbdev->ctlr->dev) {
		pr_err("hyperbus: please fill all the necessary fields!\n");
		return -EINVAL;
	}

	np = hbdev->np;
	ctlr = hbdev->ctlr;
	if (!of_device_is_compatible(np, "cypress,hyperflash"))
		return -ENODEV;

	hbdev->memtype = HYPERFLASH;

	ret = of_address_to_resource(np, 0, &res);
	if (ret)
		return ret;

	dev = ctlr->dev;
	map = &hbdev->map;
	map->size = resource_size(&res);
	map->virt = devm_ioremap_resource(dev, &res);
	if (IS_ERR(map->virt))
		return PTR_ERR(map->virt);

	map->name = dev_name(dev);
	map->bankwidth = 2;
	map->device_node = np;

	simple_map_init(map);
	ops = ctlr->ops;
	if (ops) {
		if (ops->read16)
			map->read = hyperbus_read16;
		if (ops->write16)
			map->write = hyperbus_write16;
		if (ops->copy_to)
			map->copy_to = hyperbus_copy_to;
		if (ops->copy_from)
			map->copy_from = hyperbus_copy_from;

		if (ops->calibrate && !ctlr->calibrated) {
			ret = ops->calibrate(hbdev);
			if (!ret) {
				dev_err(dev, "Calibration failed\n");
				return -ENODEV;
			}
			ctlr->calibrated = true;
		}
	}

	hbdev->mtd = do_map_probe("cfi_probe", map);
	if (!hbdev->mtd) {
		dev_err(dev, "probing of hyperbus device failed\n");
		return -ENODEV;
	}

	hbdev->mtd->dev.parent = dev;
	mtd_set_of_node(hbdev->mtd, np);

	ret = mtd_device_register(hbdev->mtd, NULL, 0);
	if (ret) {
		dev_err(dev, "failed to register mtd device\n");
		map_destroy(hbdev->mtd);
		return ret;
	}

	return 0;
}