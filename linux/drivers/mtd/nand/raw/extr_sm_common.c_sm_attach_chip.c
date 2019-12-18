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
struct TYPE_2__ {int /*<<< orphan*/  block_markbad; } ;
struct nand_chip {int badblockpos; int badblockbits; TYPE_1__ legacy; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SM_SECTOR_SIZE ; 
 scalar_t__ SM_SMALL_PAGE ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  oob_sm_ops ; 
 int /*<<< orphan*/  oob_sm_small_ops ; 
 int /*<<< orphan*/  sm_block_markbad ; 

__attribute__((used)) static int sm_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/* Bad block marker position */
	chip->badblockpos = 0x05;
	chip->badblockbits = 7;
	chip->legacy.block_markbad = sm_block_markbad;

	/* ECC layout */
	if (mtd->writesize == SM_SECTOR_SIZE)
		mtd_set_ooblayout(mtd, &oob_sm_ops);
	else if (mtd->writesize == SM_SMALL_PAGE)
		mtd_set_ooblayout(mtd, &oob_sm_small_ops);
	else
		return -ENODEV;

	return 0;
}