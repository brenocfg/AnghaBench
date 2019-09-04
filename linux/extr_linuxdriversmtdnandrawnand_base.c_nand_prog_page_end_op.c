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
typedef  int u8 ;
struct nand_sdr_timings {int /*<<< orphan*/  tPROG_max; int /*<<< orphan*/  tWB_max; } ;
struct nand_operation {int dummy; } ;
struct nand_op_instr {int dummy; } ;
struct nand_chip {int (* waitfunc ) (struct mtd_info*,struct nand_chip*) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  data_interface; scalar_t__ exec_op; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_WAIT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAND_STATUS_FAIL ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 int nand_status_op (struct nand_chip*,int*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (struct mtd_info*,struct nand_chip*) ; 

int nand_prog_page_end_op(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;
	u8 status;

	if (chip->exec_op) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_PAGEPROG,
				    PSEC_TO_NSEC(sdr->tWB_max)),
			NAND_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tPROG_max), 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);

		ret = nand_exec_op(chip, &op);
		if (ret)
			return ret;

		ret = nand_status_op(chip, &status);
		if (ret)
			return ret;
	} else {
		chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
		ret = chip->waitfunc(mtd, chip);
		if (ret < 0)
			return ret;

		status = ret;
	}

	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}