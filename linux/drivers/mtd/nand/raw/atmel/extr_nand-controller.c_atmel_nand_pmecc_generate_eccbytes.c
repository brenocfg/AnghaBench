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
struct TYPE_2__ {int steps; int /*<<< orphan*/  bytes; } ;
struct nand_chip {TYPE_1__ ecc; void* oob_poi; int /*<<< orphan*/  controller; } ;
struct mtd_oob_region {int offset; } ;
struct mtd_info {int dummy; } ;
struct atmel_nand_controller {int /*<<< orphan*/  dev; } ;
struct atmel_nand {int /*<<< orphan*/  pmecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_pmecc_get_generated_eccbytes (int /*<<< orphan*/ ,int,void*) ; 
 int atmel_pmecc_wait_rdy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_pmecc_generate_eccbytes(struct nand_chip *chip, bool raw)
{
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct atmel_nand_controller *nc;
	struct mtd_oob_region oobregion;
	void *eccbuf;
	int ret, i;

	nc = to_nand_controller(chip->controller);

	if (raw)
		return 0;

	ret = atmel_pmecc_wait_rdy(nand->pmecc);
	if (ret) {
		dev_err(nc->dev,
			"Failed to transfer NAND page data (err = %d)\n",
			ret);
		return ret;
	}

	mtd_ooblayout_ecc(mtd, 0, &oobregion);
	eccbuf = chip->oob_poi + oobregion.offset;

	for (i = 0; i < chip->ecc.steps; i++) {
		atmel_pmecc_get_generated_eccbytes(nand->pmecc, i,
						   eccbuf);
		eccbuf += chip->ecc.bytes;
	}

	return 0;
}