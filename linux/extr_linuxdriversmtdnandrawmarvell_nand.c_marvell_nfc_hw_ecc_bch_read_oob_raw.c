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
struct TYPE_2__ {int (* read_page_raw ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ;} ;
struct nand_chip {int pagebuf; int /*<<< orphan*/  data_buf; TYPE_1__ ecc; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int stub1 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_bch_read_oob_raw(struct mtd_info *mtd,
					       struct nand_chip *chip, int page)
{
	/* Invalidate page cache */
	chip->pagebuf = -1;

	return chip->ecc.read_page_raw(mtd, chip, chip->data_buf, true, page);
}