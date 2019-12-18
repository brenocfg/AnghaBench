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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int nand_read_data_op (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

int nand_read_page_raw(struct nand_chip *chip, uint8_t *buf, int oob_required,
		       int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	ret = nand_read_page_op(chip, page, 0, buf, mtd->writesize);
	if (ret)
		return ret;

	if (oob_required) {
		ret = nand_read_data_op(chip, chip->oob_poi, mtd->oobsize,
					false);
		if (ret)
			return ret;
	}

	return 0;
}