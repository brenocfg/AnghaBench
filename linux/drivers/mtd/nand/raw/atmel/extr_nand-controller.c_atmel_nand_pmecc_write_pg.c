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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;
struct atmel_nand {int /*<<< orphan*/  pmecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_WRITE ; 
 int /*<<< orphan*/  atmel_nand_pmecc_disable (struct nand_chip*,int) ; 
 int atmel_nand_pmecc_enable (struct nand_chip*,int /*<<< orphan*/ ,int) ; 
 int atmel_nand_pmecc_generate_eccbytes (struct nand_chip*,int) ; 
 int /*<<< orphan*/  atmel_nand_write_buf (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_pmecc_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 

__attribute__((used)) static int atmel_nand_pmecc_write_pg(struct nand_chip *chip, const u8 *buf,
				     bool oob_required, int page, bool raw)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct atmel_nand *nand = to_atmel_nand(chip);
	int ret;

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	ret = atmel_nand_pmecc_enable(chip, NAND_ECC_WRITE, raw);
	if (ret)
		return ret;

	atmel_nand_write_buf(chip, buf, mtd->writesize);

	ret = atmel_nand_pmecc_generate_eccbytes(chip, raw);
	if (ret) {
		atmel_pmecc_disable(nand->pmecc);
		return ret;
	}

	atmel_nand_pmecc_disable(chip, raw);

	atmel_nand_write_buf(chip, chip->oob_poi, mtd->oobsize);

	return nand_prog_page_end_op(chip);
}