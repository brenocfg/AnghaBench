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
struct nand_chip {int chip_shift; } ;
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_block_checkbad (struct nand_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_deselect_target (struct nand_chip*) ; 
 int nand_get_device (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_release_device (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_select_target (struct nand_chip*,int) ; 

__attribute__((used)) static int nand_block_isbad(struct mtd_info *mtd, loff_t offs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int chipnr = (int)(offs >> chip->chip_shift);
	int ret;

	/* Select the NAND device */
	ret = nand_get_device(chip);
	if (ret)
		return ret;

	nand_select_target(chip, chipnr);

	ret = nand_block_checkbad(chip, offs, 0);

	nand_deselect_target(chip);
	nand_release_device(chip);

	return ret;
}