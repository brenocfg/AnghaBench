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
struct nand_ecc_ctrl {int steps; int bytes; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct mtd_oob_region {int length; scalar_t__ offset; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ BBM_SIZE ; 
 int ERANGE ; 
 scalar_t__ METADATA_SIZE ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static int oob_ecc(struct mtd_info *mtd, int idx, struct mtd_oob_region *res)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;

	if (idx >= ecc->steps)
		return -ERANGE;

	res->offset = BBM_SIZE + METADATA_SIZE + ecc->bytes * idx;
	res->length = ecc->bytes;

	return 0;
}