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
struct TYPE_2__ {int size; int bytes; int steps; int (* write_page_raw ) (struct nand_chip*,int /*<<< orphan*/  const*,int,int) ;int /*<<< orphan*/  total; int /*<<< orphan*/  (* calculate ) (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * calc_buf; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int mtd_ooblayout_set_eccbytes (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int stub2 (struct nand_chip*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int nand_write_page_swecc(struct nand_chip *chip, const uint8_t *buf,
				 int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int i, eccsize = chip->ecc.size, ret;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *ecc_calc = chip->ecc.calc_buf;
	const uint8_t *p = buf;

	/* Software ECC calculation */
	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(chip, p, &ecc_calc[i]);

	ret = mtd_ooblayout_set_eccbytes(mtd, ecc_calc, chip->oob_poi, 0,
					 chip->ecc.total);
	if (ret)
		return ret;

	return chip->ecc.write_page_raw(chip, buf, 1, page);
}