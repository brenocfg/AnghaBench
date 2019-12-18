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
struct mtd_info {unsigned int oobsize; scalar_t__ writesize; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NAND_CMD_READOOB ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 int nand_read_page_op (struct nand_chip*,unsigned int,scalar_t__,void*,unsigned int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,void*,unsigned int) ; 

int nand_read_oob_op(struct nand_chip *chip, unsigned int page,
		     unsigned int offset_in_oob, void *buf, unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_oob + len > mtd->oobsize)
		return -EINVAL;

	if (nand_has_exec_op(chip))
		return nand_read_page_op(chip, page,
					 mtd->writesize + offset_in_oob,
					 buf, len);

	chip->legacy.cmdfunc(chip, NAND_CMD_READOOB, offset_in_oob, page);
	if (len)
		chip->legacy.read_buf(chip, buf, len);

	return 0;
}