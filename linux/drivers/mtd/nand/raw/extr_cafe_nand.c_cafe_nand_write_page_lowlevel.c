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
struct TYPE_2__ {int /*<<< orphan*/  (* write_buf ) (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct nand_chip {int /*<<< orphan*/  oob_poi; TYPE_1__ legacy; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;
struct cafe_priv {int ctl2; } ;

/* Variables and functions */
 struct cafe_priv* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cafe_nand_write_page_lowlevel(struct nand_chip *chip,
					 const uint8_t *buf, int oob_required,
					 int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct cafe_priv *cafe = nand_get_controller_data(chip);

	nand_prog_page_begin_op(chip, page, 0, buf, mtd->writesize);
	chip->legacy.write_buf(chip, chip->oob_poi, mtd->oobsize);

	/* Set up ECC autogeneration */
	cafe->ctl2 |= (1<<30);

	return nand_prog_page_end_op(chip);
}