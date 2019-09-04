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
struct nand_sdr_timings {int /*<<< orphan*/  tADL_min; } ;
struct nand_operation {int /*<<< orphan*/  ninstrs; } ;
struct nand_op_instr {int dummy; } ;
struct nand_chip {int /*<<< orphan*/  (* read_byte ) (struct mtd_info*) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  data_interface; scalar_t__ exec_op; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_STATUS ; 
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_8BIT_DATA_IN (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*) ; 

int nand_status_op(struct nand_chip *chip, u8 *status)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (chip->exec_op) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_STATUS,
				    PSEC_TO_NSEC(sdr->tADL_min)),
			NAND_OP_8BIT_DATA_IN(1, status, 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);

		if (!status)
			op.ninstrs--;

		return nand_exec_op(chip, &op);
	}

	chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);
	if (status)
		*status = chip->read_byte(mtd);

	return 0;
}