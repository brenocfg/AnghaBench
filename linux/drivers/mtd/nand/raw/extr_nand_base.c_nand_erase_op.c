#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct nand_sdr_timings {int /*<<< orphan*/  tBERS_max; int /*<<< orphan*/  tWB_max; } ;
struct nand_operation {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  naddrs; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct nand_op_instr {TYPE_2__ ctx; } ;
struct TYPE_6__ {int (* waitfunc ) (struct nand_chip*) ;int /*<<< orphan*/  (* cmdfunc ) (struct nand_chip*,int /*<<< orphan*/ ,int,int) ;} ;
struct nand_chip {unsigned int phys_erase_shift; unsigned int page_shift; int options; TYPE_3__ legacy; int /*<<< orphan*/  cur_cs; int /*<<< orphan*/  data_interface; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NAND_CMD_ERASE1 ; 
 int /*<<< orphan*/  NAND_CMD_ERASE2 ; 
 struct nand_operation NAND_OPERATION (int /*<<< orphan*/ ,struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_ADDR (int,unsigned int*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_WAIT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAND_ROW_ADDR_3 ; 
 unsigned int NAND_STATUS_FAIL ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 scalar_t__ nand_has_exec_op (struct nand_chip*) ; 
 int nand_status_op (struct nand_chip*,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 
 int stub3 (struct nand_chip*) ; 

int nand_erase_op(struct nand_chip *chip, unsigned int eraseblock)
{
	unsigned int page = eraseblock <<
			    (chip->phys_erase_shift - chip->page_shift);
	int ret;
	u8 status;

	if (nand_has_exec_op(chip)) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		u8 addrs[3] = {	page, page >> 8, page >> 16 };
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_ERASE1, 0),
			NAND_OP_ADDR(2, addrs, 0),
			NAND_OP_CMD(NAND_CMD_ERASE2,
				    PSEC_TO_MSEC(sdr->tWB_max)),
			NAND_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tBERS_max), 0),
		};
		struct nand_operation op = NAND_OPERATION(chip->cur_cs, instrs);

		if (chip->options & NAND_ROW_ADDR_3)
			instrs[1].ctx.addr.naddrs++;

		ret = nand_exec_op(chip, &op);
		if (ret)
			return ret;

		ret = nand_status_op(chip, &status);
		if (ret)
			return ret;
	} else {
		chip->legacy.cmdfunc(chip, NAND_CMD_ERASE1, -1, page);
		chip->legacy.cmdfunc(chip, NAND_CMD_ERASE2, -1, -1);

		ret = chip->legacy.waitfunc(chip);
		if (ret < 0)
			return ret;

		status = ret;
	}

	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}