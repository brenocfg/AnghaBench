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
struct nand_chip {int (* waitfunc ) (struct mtd_info*,struct nand_chip*) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,void const*,unsigned int) ;scalar_t__ exec_op; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  NAND_CMD_SEQIN ; 
 int NAND_STATUS_FAIL ; 
 int nand_exec_prog_page_op (struct nand_chip*,unsigned int,unsigned int,void const*,unsigned int,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,void const*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub4 (struct mtd_info*,struct nand_chip*) ; 

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

	if (chip->exec_op) {
		status = nand_exec_prog_page_op(chip, page, offset_in_page, buf,
						len, true);
	} else {
		chip->cmdfunc(mtd, NAND_CMD_SEQIN, offset_in_page, page);
		chip->write_buf(mtd, buf, len);
		chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
		status = chip->waitfunc(mtd, chip);
	}

	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}