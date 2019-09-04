#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct mtd_info {char* name; } ;
struct atmel_nand_controller {TYPE_4__* dev; TYPE_2__* caps; } ;
struct atmel_nand {TYPE_3__* cs; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {scalar_t__ legacy_of_bindings; TYPE_1__* ops; } ;
struct TYPE_7__ {int (* ecc_init ) (struct nand_chip*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 char* devm_kasprintf (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int stub1 (struct nand_chip*) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_attach_chip(struct nand_chip *chip)
{
	struct atmel_nand_controller *nc = to_nand_controller(chip->controller);
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	ret = nc->caps->ops->ecc_init(chip);
	if (ret)
		return ret;

	if (nc->caps->legacy_of_bindings || !nc->dev->of_node) {
		/*
		 * We keep the MTD name unchanged to avoid breaking platforms
		 * where the MTD cmdline parser is used and the bootloader
		 * has not been updated to use the new naming scheme.
		 */
		mtd->name = "atmel_nand";
	} else if (!mtd->name) {
		/*
		 * If the new bindings are used and the bootloader has not been
		 * updated to pass a new mtdparts parameter on the cmdline, you
		 * should define the following property in your nand node:
		 *
		 *	label = "atmel_nand";
		 *
		 * This way, mtd->name will be set by the core when
		 * nand_set_flash_node() is called.
		 */
		mtd->name = devm_kasprintf(nc->dev, GFP_KERNEL,
					   "%s:nand.%d", dev_name(nc->dev),
					   nand->cs[0].id);
		if (!mtd->name) {
			dev_err(nc->dev, "Failed to allocate mtd->name\n");
			return -ENOMEM;
		}
	}

	return 0;
}