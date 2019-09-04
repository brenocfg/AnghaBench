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
struct nand_chip {int /*<<< orphan*/  oob_poi; int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_nand_write_page_raw_syndrome(struct mtd_info *mtd,
						struct nand_chip *chip,
						const uint8_t *buf,
						int oob_required, int page)
{
	/* Raw writes can just use the FIFO interface */
	nand_prog_page_begin_op(chip, page, 0, buf,
				chip->ecc.size * chip->ecc.steps);
	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return nand_prog_page_end_op(chip);
}