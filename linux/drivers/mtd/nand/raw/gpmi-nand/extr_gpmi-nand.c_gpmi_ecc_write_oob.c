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
struct nand_chip {scalar_t__ oob_poi; } ;
struct mtd_oob_region {int /*<<< orphan*/  length; scalar_t__ offset; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  mtd_ooblayout_free (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 int /*<<< orphan*/  nand_is_slc (struct nand_chip*) ; 
 int nand_prog_page_op (struct nand_chip*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_ecc_write_oob(struct nand_chip *chip, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mtd_oob_region of = { };

	/* Do we have available oob area? */
	mtd_ooblayout_free(mtd, 0, &of);
	if (!of.length)
		return -EPERM;

	if (!nand_is_slc(chip))
		return -EPERM;

	return nand_prog_page_op(chip, page, mtd->writesize + of.offset,
				 chip->oob_poi + of.offset, of.length);
}