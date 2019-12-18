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
struct TYPE_2__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  strength; int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {scalar_t__ oobsize; } ;
struct denali_controller {int /*<<< orphan*/  dev; scalar_t__ oob_skip_bytes; int /*<<< orphan*/  ecc_caps; } ;

/* Variables and functions */
 int denali_multidev_fixup (struct nand_chip*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int nand_ecc_choose_conf (struct nand_chip*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct denali_controller* to_denali_controller (struct nand_chip*) ; 

__attribute__((used)) static int denali_attach_chip(struct nand_chip *chip)
{
	struct denali_controller *denali = to_denali_controller(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	ret = nand_ecc_choose_conf(chip, denali->ecc_caps,
				   mtd->oobsize - denali->oob_skip_bytes);
	if (ret) {
		dev_err(denali->dev, "Failed to setup ECC settings.\n");
		return ret;
	}

	dev_dbg(denali->dev,
		"chosen ECC settings: step=%d, strength=%d, bytes=%d\n",
		chip->ecc.size, chip->ecc.strength, chip->ecc.bytes);

	ret = denali_multidev_fixup(chip);
	if (ret)
		return ret;

	return 0;
}