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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int steps; int size; int bytes; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; TYPE_1__ ecc; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct denali_nand_info {int oob_skip_bytes; } ;

/* Variables and functions */
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,size_t,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nand_change_write_column_op (struct nand_chip*,size_t,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void denali_oob_xfer(struct mtd_info *mtd, struct nand_chip *chip,
			    int page, int write)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	int writesize = mtd->writesize;
	int oobsize = mtd->oobsize;
	uint8_t *bufpoi = chip->oob_poi;
	int ecc_steps = chip->ecc.steps;
	int ecc_size = chip->ecc.size;
	int ecc_bytes = chip->ecc.bytes;
	int oob_skip = denali->oob_skip_bytes;
	size_t size = writesize + oobsize;
	int i, pos, len;

	/* BBM at the beginning of the OOB area */
	if (write)
		nand_prog_page_begin_op(chip, page, writesize, bufpoi,
					oob_skip);
	else
		nand_read_page_op(chip, page, writesize, bufpoi, oob_skip);
	bufpoi += oob_skip;

	/* OOB ECC */
	for (i = 0; i < ecc_steps; i++) {
		pos = ecc_size + i * (ecc_size + ecc_bytes);
		len = ecc_bytes;

		if (pos >= writesize)
			pos += oob_skip;
		else if (pos + len > writesize)
			len = writesize - pos;

		if (write)
			nand_change_write_column_op(chip, pos, bufpoi, len,
						    false);
		else
			nand_change_read_column_op(chip, pos, bufpoi, len,
						   false);
		bufpoi += len;
		if (len < ecc_bytes) {
			len = ecc_bytes - len;
			if (write)
				nand_change_write_column_op(chip, writesize +
							    oob_skip, bufpoi,
							    len, false);
			else
				nand_change_read_column_op(chip, writesize +
							   oob_skip, bufpoi,
							   len, false);
			bufpoi += len;
		}
	}

	/* OOB free */
	len = oobsize - (bufpoi - chip->oob_poi);
	if (write)
		nand_change_write_column_op(chip, size - len, bufpoi, len,
					    false);
	else
		nand_change_read_column_op(chip, size - len, bufpoi, len,
					   false);
}