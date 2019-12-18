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
struct TYPE_2__ {int /*<<< orphan*/  (* read_buf ) (struct nand_chip*,void*,unsigned int) ;int /*<<< orphan*/  (* cmdfunc ) (struct nand_chip*,int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 int nand_lp_exec_read_page_op (struct nand_chip*,unsigned int,unsigned int,void*,unsigned int) ; 
 int nand_sp_exec_read_page_op (struct nand_chip*,unsigned int,unsigned int,void*,unsigned int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,void*,unsigned int) ; 

int nand_read_page_op(struct nand_chip *chip, unsigned int page,
		      unsigned int offset_in_page, void *buf, unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	if (nand_has_exec_op(chip)) {
		if (mtd->writesize > 512)
			return nand_lp_exec_read_page_op(chip, page,
							 offset_in_page, buf,
							 len);

		return nand_sp_exec_read_page_op(chip, page, offset_in_page,
						 buf, len);
	}

	chip->legacy.cmdfunc(chip, NAND_CMD_READ0, offset_in_page, page);
	if (len)
		chip->legacy.read_buf(chip, buf, len);

	return 0;
}