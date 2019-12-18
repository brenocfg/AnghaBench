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
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct mtd_info {TYPE_1__ dev; int /*<<< orphan*/  owner; } ;
struct map_info {int /*<<< orphan*/  copy_to; int /*<<< orphan*/  copy_from; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  virt; int /*<<< orphan*/  bankwidth; } ;
struct cobalt {TYPE_2__* pci_dev; struct mtd_info* mtd; int /*<<< orphan*/  bar1; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cobalt_err (char*) ; 
 struct map_info cobalt_flash_map ; 
 struct mtd_info* do_map_probe (char*,struct map_info*) ; 
 int /*<<< orphan*/  flash_copy_from ; 
 int /*<<< orphan*/  flash_copy_to ; 
 int /*<<< orphan*/  flash_read16 ; 
 int /*<<< orphan*/  flash_write16 ; 
 int /*<<< orphan*/  map_bankwidth_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cobalt_flash_probe(struct cobalt *cobalt)
{
	struct map_info *map = &cobalt_flash_map;
	struct mtd_info *mtd;

	BUG_ON(!map_bankwidth_supported(map->bankwidth));
	map->virt = cobalt->bar1;
	map->read = flash_read16;
	map->write = flash_write16;
	map->copy_from = flash_copy_from;
	map->copy_to = flash_copy_to;

	mtd = do_map_probe("cfi_probe", map);
	cobalt->mtd = mtd;
	if (!mtd) {
		cobalt_err("Probe CFI flash failed!\n");
		return -1;
	}

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &cobalt->pci_dev->dev;
	mtd_device_register(mtd, NULL, 0);
	return 0;
}