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
struct TYPE_2__ {int /*<<< orphan*/  (* read_buf ) (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct nand_chip {int /*<<< orphan*/  oob_poi; TYPE_1__ legacy; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flctl_read_page_hwecc(struct nand_chip *chip, uint8_t *buf,
				 int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	nand_read_page_op(chip, page, 0, buf, mtd->writesize);
	if (oob_required)
		chip->legacy.read_buf(chip, chip->oob_poi, mtd->oobsize);
	return 0;
}