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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int (* write_subpage ) (struct mtd_info*,struct nand_chip*,scalar_t__,int,int /*<<< orphan*/  const*,int,int) ;int (* write_page_raw ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*,int,int) ;int (* write_page ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*,int,int) ;} ;
struct nand_chip {int options; TYPE_1__ ecc; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int NAND_NO_SUBPAGE_WRITE ; 
 int stub1 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*,int,int) ; 
 int stub2 (struct mtd_info*,struct nand_chip*,scalar_t__,int,int /*<<< orphan*/  const*,int,int) ; 
 int stub3 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nand_write_page(struct mtd_info *mtd, struct nand_chip *chip,
		uint32_t offset, int data_len, const uint8_t *buf,
		int oob_required, int page, int raw)
{
	int status, subpage;

	if (!(chip->options & NAND_NO_SUBPAGE_WRITE) &&
		chip->ecc.write_subpage)
		subpage = offset || (data_len < mtd->writesize);
	else
		subpage = 0;

	if (unlikely(raw))
		status = chip->ecc.write_page_raw(mtd, chip, buf,
						  oob_required, page);
	else if (subpage)
		status = chip->ecc.write_subpage(mtd, chip, offset, data_len,
						 buf, oob_required, page);
	else
		status = chip->ecc.write_page(mtd, chip, buf, oob_required,
					      page);

	if (status < 0)
		return status;

	return 0;
}