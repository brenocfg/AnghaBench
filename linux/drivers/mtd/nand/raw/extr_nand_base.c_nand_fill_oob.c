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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {scalar_t__ oob_poi; } ;
struct mtd_oob_ops {int mode; scalar_t__ ooboffs; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  MTD_OPS_AUTO_OOB 130 
#define  MTD_OPS_PLACE_OOB 129 
#define  MTD_OPS_RAW 128 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int mtd_ooblayout_set_databytes (struct mtd_info*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,size_t) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static uint8_t *nand_fill_oob(struct nand_chip *chip, uint8_t *oob, size_t len,
			      struct mtd_oob_ops *ops)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	/*
	 * Initialise to all 0xFF, to avoid the possibility of left over OOB
	 * data from a previous OOB read.
	 */
	memset(chip->oob_poi, 0xff, mtd->oobsize);

	switch (ops->mode) {

	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_RAW:
		memcpy(chip->oob_poi + ops->ooboffs, oob, len);
		return oob + len;

	case MTD_OPS_AUTO_OOB:
		ret = mtd_ooblayout_set_databytes(mtd, oob, chip->oob_poi,
						  ops->ooboffs, len);
		BUG_ON(ret);
		return oob + len;

	default:
		BUG();
	}
	return NULL;
}