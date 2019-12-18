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
struct TYPE_2__ {int (* waitfunc ) (struct nand_chip*) ;int /*<<< orphan*/  (* cmdfunc ) (struct nand_chip*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* write_buf ) (struct nand_chip*,void const*,unsigned int) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  NAND_CMD_SEQIN ; 
 int NAND_STATUS_FAIL ; 
 int nand_exec_prog_page_op (struct nand_chip*,unsigned int,unsigned int,void const*,unsigned int,int) ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,void const*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (struct nand_chip*) ; 

int nand_prog_page_op(struct nand_chip *chip, unsigned int page,
		      unsigned int offset_in_page, const void *buf,
		      unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int status;

	if (!len || !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	if (nand_has_exec_op(chip)) {
		status = nand_exec_prog_page_op(chip, page, offset_in_page, buf,
						len, true);
	} else {
		chip->legacy.cmdfunc(chip, NAND_CMD_SEQIN, offset_in_page,
				     page);
		chip->legacy.write_buf(chip, buf, len);
		chip->legacy.cmdfunc(chip, NAND_CMD_PAGEPROG, -1, -1);
		status = chip->legacy.waitfunc(chip);
	}

	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}