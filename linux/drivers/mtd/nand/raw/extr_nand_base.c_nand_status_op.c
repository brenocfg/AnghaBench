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
typedef  int /*<<< orphan*/  u8 ;
struct nand_sdr_timings {int /*<<< orphan*/  tADL_min; } ;
struct nand_operation {int /*<<< orphan*/  ninstrs; } ;
struct nand_op_instr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_byte ) (struct nand_chip*) ;int /*<<< orphan*/  (* cmdfunc ) (struct nand_chip*,int /*<<< orphan*/ ,int,int) ;} ;
struct nand_chip {TYPE_1__ legacy; int /*<<< orphan*/  cur_cs; int /*<<< orphan*/  data_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_STATUS ; 
 struct nand_operation NAND_OPERATION (int /*<<< orphan*/ ,struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_8BIT_DATA_IN (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*) ; 

int nand_status_op(struct nand_chip *chip, u8 *status)
{
	if (nand_has_exec_op(chip)) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_STATUS,
				    PSEC_TO_NSEC(sdr->tADL_min)),
			NAND_OP_8BIT_DATA_IN(1, status, 0),
		};
		struct nand_operation op = NAND_OPERATION(chip->cur_cs, instrs);

		if (!status)
			op.ninstrs--;

		return nand_exec_op(chip, &op);
	}

	chip->legacy.cmdfunc(chip, NAND_CMD_STATUS, -1, -1);
	if (status)
		*status = chip->legacy.read_byte(chip);

	return 0;
}