#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nand_ecc_ctrl {int size; int strength; } ;
struct nand_chip {int ecc_step_ds; int ecc_strength_ds; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static bool nand_ecc_strength_good(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int corr, ds_corr;

	if (ecc->size == 0 || chip->ecc_step_ds == 0)
		/* Not enough information */
		return true;

	/*
	 * We get the number of corrected bits per page to compare
	 * the correction density.
	 */
	corr = (mtd->writesize * ecc->strength) / ecc->size;
	ds_corr = (mtd->writesize * chip->ecc_strength_ds) / chip->ecc_step_ds;

	return corr >= ds_corr && ecc->strength >= chip->ecc_strength_ds;
}