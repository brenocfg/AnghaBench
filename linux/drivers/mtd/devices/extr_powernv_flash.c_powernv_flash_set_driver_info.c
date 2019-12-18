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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device* parent; } ;
struct mtd_info {int writebufsize; int writesize; TYPE_1__ dev; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _erase; int /*<<< orphan*/  owner; int /*<<< orphan*/  erasesize; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_NORFLASH ; 
 int /*<<< orphan*/  MTD_WRITEABLE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_of_node (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u64 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powernv_flash_erase ; 
 int /*<<< orphan*/  powernv_flash_read ; 
 int /*<<< orphan*/  powernv_flash_write ; 

__attribute__((used)) static int powernv_flash_set_driver_info(struct device *dev,
		struct mtd_info *mtd)
{
	u64 size;
	u32 erase_size;
	int rc;

	rc = of_property_read_u32(dev->of_node, "ibm,flash-block-size",
			&erase_size);
	if (rc) {
		dev_err(dev, "couldn't get resource block size information\n");
		return rc;
	}

	rc = of_property_read_u64(dev->of_node, "reg", &size);
	if (rc) {
		dev_err(dev, "couldn't get resource size information\n");
		return rc;
	}

	/*
	 * Going to have to check what details I need to set and how to
	 * get them
	 */
	mtd->name = devm_kasprintf(dev, GFP_KERNEL, "%pOFP", dev->of_node);
	mtd->type = MTD_NORFLASH;
	mtd->flags = MTD_WRITEABLE;
	mtd->size = size;
	mtd->erasesize = erase_size;
	mtd->writebufsize = mtd->writesize = 1;
	mtd->owner = THIS_MODULE;
	mtd->_erase = powernv_flash_erase;
	mtd->_read = powernv_flash_read;
	mtd->_write = powernv_flash_write;
	mtd->dev.parent = dev;
	mtd_set_of_node(mtd, dev->of_node);
	return 0;
}