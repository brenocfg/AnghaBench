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
struct nand_chip {int chip_shift; int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;} ;
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FL_READING ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_block_checkbad (struct mtd_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release_device (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int) ; 

__attribute__((used)) static int nand_block_isbad(struct mtd_info *mtd, loff_t offs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int chipnr = (int)(offs >> chip->chip_shift);
	int ret;

	/* Select the NAND device */
	nand_get_device(mtd, FL_READING);
	chip->select_chip(mtd, chipnr);

	ret = nand_block_checkbad(mtd, offs, 0);

	chip->select_chip(mtd, -1);
	nand_release_device(mtd);

	return ret;
}