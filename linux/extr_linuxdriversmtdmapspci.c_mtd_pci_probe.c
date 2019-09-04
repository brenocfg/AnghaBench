#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int dummy; } ;
struct mtd_pci_info {int (* init ) (struct pci_dev*,struct map_pci_info*) ;int /*<<< orphan*/  map_name; int /*<<< orphan*/  translate; int /*<<< orphan*/  (* exit ) (struct pci_dev*,struct map_pci_info*) ;} ;
struct mtd_info {int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct map_pci_info {int /*<<< orphan*/  (* exit ) (struct pci_dev*,struct map_pci_info*) ;TYPE_1__ map; int /*<<< orphan*/  translate; struct pci_dev* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct mtd_info* do_map_probe (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct map_pci_info*) ; 
 struct map_pci_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ mtd_pci_map ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct mtd_info*) ; 
 int stub1 (struct pci_dev*,struct map_pci_info*) ; 
 int /*<<< orphan*/  stub2 (struct pci_dev*,struct map_pci_info*) ; 

__attribute__((used)) static int mtd_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct mtd_pci_info *info = (struct mtd_pci_info *)id->driver_data;
	struct map_pci_info *map = NULL;
	struct mtd_info *mtd = NULL;
	int err;

	err = pci_enable_device(dev);
	if (err)
		goto out;

	err = pci_request_regions(dev, "pci mtd");
	if (err)
		goto out;

	map = kmalloc(sizeof(*map), GFP_KERNEL);
	err = -ENOMEM;
	if (!map)
		goto release;

	map->map       = mtd_pci_map;
	map->map.name  = pci_name(dev);
	map->dev       = dev;
	map->exit      = info->exit;
	map->translate = info->translate;

	err = info->init(dev, map);
	if (err)
		goto release;

	mtd = do_map_probe(info->map_name, &map->map);
	err = -ENODEV;
	if (!mtd)
		goto release;

	mtd->owner = THIS_MODULE;
	mtd_device_register(mtd, NULL, 0);

	pci_set_drvdata(dev, mtd);

	return 0;

release:
	if (map) {
		map->exit(dev, map);
		kfree(map);
	}

	pci_release_regions(dev);
out:
	return err;
}