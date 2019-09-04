#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; } ;
struct atmel_nand {TYPE_2__* activecs; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cs; int /*<<< orphan*/  ncmds; int /*<<< orphan*/ * cmds; } ;
struct atmel_hsmc_nand_controller {TYPE_4__ base; TYPE_3__ op; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; TYPE_1__ rb; } ;

/* Variables and functions */
 scalar_t__ ATMEL_NAND_NATIVE_RB ; 
 int /*<<< orphan*/  ATMEL_NFC_READ_DATA ; 
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int /*<<< orphan*/  NAND_CMD_READSTART ; 
 int /*<<< orphan*/  NAND_ECC_READ ; 
 int atmel_nand_pmecc_correct_data (struct nand_chip*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atmel_nand_pmecc_disable (struct nand_chip*,int) ; 
 int atmel_nand_pmecc_enable (struct nand_chip*,int /*<<< orphan*/ ,int) ; 
 int atmel_nand_pmecc_read_pg (struct nand_chip*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  atmel_nfc_copy_from_sram (struct nand_chip*,int /*<<< orphan*/ *,int) ; 
 int atmel_nfc_exec_op (struct atmel_hsmc_nand_controller*,int) ; 
 int /*<<< orphan*/  atmel_nfc_set_op_addr (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_hsmc_nand_controller* to_hsmc_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_hsmc_nand_pmecc_read_pg(struct nand_chip *chip, u8 *buf,
					 bool oob_required, int page,
					 bool raw)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_hsmc_nand_controller *nc;
	int ret;

	nc = to_hsmc_nand_controller(chip->controller);

	/*
	 * Optimized read page accessors only work when the NAND R/B pin is
	 * connected to a native SoC R/B pin. If that's not the case, fallback
	 * to the non-optimized one.
	 */
	if (nand->activecs->rb.type != ATMEL_NAND_NATIVE_RB) {
		nand_read_page_op(chip, page, 0, NULL, 0);

		return atmel_nand_pmecc_read_pg(chip, buf, oob_required, page,
						raw);
	}

	nc->op.cmds[nc->op.ncmds++] = NAND_CMD_READ0;

	if (mtd->writesize > 512)
		nc->op.cmds[nc->op.ncmds++] = NAND_CMD_READSTART;

	atmel_nfc_set_op_addr(chip, page, 0x0);
	nc->op.cs = nand->activecs->id;
	nc->op.data = ATMEL_NFC_READ_DATA;

	ret = atmel_nand_pmecc_enable(chip, NAND_ECC_READ, raw);
	if (ret)
		return ret;

	ret = atmel_nfc_exec_op(nc, false);
	if (ret) {
		atmel_nand_pmecc_disable(chip, raw);
		dev_err(nc->base.dev,
			"Failed to load NAND page data (err = %d)\n",
			ret);
		return ret;
	}

	atmel_nfc_copy_from_sram(chip, buf, true);

	ret = atmel_nand_pmecc_correct_data(chip, buf, raw);

	atmel_nand_pmecc_disable(chip, raw);

	return ret;
}