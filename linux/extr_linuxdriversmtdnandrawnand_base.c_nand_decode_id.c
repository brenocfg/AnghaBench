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
struct nand_flash_dev {int pagesize; int /*<<< orphan*/  erasesize; } ;
struct nand_chip {int bits_per_cell; } ;
struct mtd_info {int writesize; int oobsize; int /*<<< orphan*/  erasesize; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void nand_decode_id(struct nand_chip *chip, struct nand_flash_dev *type)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	mtd->erasesize = type->erasesize;
	mtd->writesize = type->pagesize;
	mtd->oobsize = mtd->writesize / 32;

	/* All legacy ID NAND are small-page, SLC */
	chip->bits_per_cell = 1;
}