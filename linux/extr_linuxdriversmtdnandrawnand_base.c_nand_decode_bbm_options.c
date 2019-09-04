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
struct nand_chip {int options; int /*<<< orphan*/  badblockpos; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_LARGE_BADBLOCK_POS ; 
 int /*<<< orphan*/  NAND_SMALL_BADBLOCK_POS ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static void nand_decode_bbm_options(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/* Set the bad block position */
	if (mtd->writesize > 512 || (chip->options & NAND_BUSWIDTH_16))
		chip->badblockpos = NAND_LARGE_BADBLOCK_POS;
	else
		chip->badblockpos = NAND_SMALL_BADBLOCK_POS;
}