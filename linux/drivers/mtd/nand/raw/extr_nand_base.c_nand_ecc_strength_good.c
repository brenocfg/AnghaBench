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
struct nand_ecc_ctrl {int size; int strength; } ;
struct TYPE_3__ {int step_size; int strength; } ;
struct TYPE_4__ {TYPE_1__ eccreq; } ;
struct nand_chip {TYPE_2__ base; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static bool nand_ecc_strength_good(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int corr, ds_corr;

	if (ecc->size == 0 || chip->base.eccreq.step_size == 0)
		/* Not enough information */
		return true;

	/*
	 * We get the number of corrected bits per page to compare
	 * the correction density.
	 */
	corr = (mtd->writesize * ecc->strength) / ecc->size;
	ds_corr = (mtd->writesize * chip->base.eccreq.strength) /
		  chip->base.eccreq.step_size;

	return corr >= ds_corr && ecc->strength >= chip->base.eccreq.strength;
}