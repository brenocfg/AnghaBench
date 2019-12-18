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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct atmel_nand_controller {int /*<<< orphan*/  chips; int /*<<< orphan*/  dev; TYPE_2__* caps; } ;
struct atmel_nand {int /*<<< orphan*/  node; int /*<<< orphan*/  numcs; scalar_t__ cdgpio; struct nand_chip base; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* nand_init ) (struct atmel_nand_controller*,struct atmel_nand*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpiod_get_value (scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_cleanup (struct nand_chip*) ; 
 int nand_scan (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct atmel_nand_controller*,struct atmel_nand*) ; 

__attribute__((used)) static int
atmel_nand_controller_add_nand(struct atmel_nand_controller *nc,
			       struct atmel_nand *nand)
{
	struct nand_chip *chip = &nand->base;
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	/* No card inserted, skip this NAND. */
	if (nand->cdgpio && gpiod_get_value(nand->cdgpio)) {
		dev_info(nc->dev, "No SmartMedia card inserted.\n");
		return 0;
	}

	nc->caps->ops->nand_init(nc, nand);

	ret = nand_scan(chip, nand->numcs);
	if (ret) {
		dev_err(nc->dev, "NAND scan failed: %d\n", ret);
		return ret;
	}

	ret = mtd_device_register(mtd, NULL, 0);
	if (ret) {
		dev_err(nc->dev, "Failed to register mtd device: %d\n", ret);
		nand_cleanup(chip);
		return ret;
	}

	list_add_tail(&nand->node, &nc->chips);

	return 0;
}