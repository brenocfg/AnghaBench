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
struct TYPE_2__ {int size; int steps; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;TYPE_1__ ecc; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lpc32xx_nand_read_page_raw_syndrome(struct mtd_info *mtd,
					       struct nand_chip *chip,
					       uint8_t *buf, int oob_required,
					       int page)
{
	/* Issue read command */
	nand_read_page_op(chip, page, 0, NULL, 0);

	/* Raw reads can just use the FIFO interface */
	chip->read_buf(mtd, buf, chip->ecc.size * chip->ecc.steps);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	return 0;
}