#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct nand_sdr_timings {int /*<<< orphan*/  tRR_min; int /*<<< orphan*/  tR_max; int /*<<< orphan*/  tWB_max; } ;
struct nand_operation {int /*<<< orphan*/  ninstrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  naddrs; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;
struct nand_op_instr {TYPE_2__ ctx; } ;
struct nand_chip {int options; int /*<<< orphan*/  cur_cs; int /*<<< orphan*/  data_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int /*<<< orphan*/  NAND_CMD_READSTART ; 
 struct nand_operation NAND_OPERATION (int /*<<< orphan*/ ,struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_ADDR (int,unsigned int*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_DATA_IN (unsigned int,void*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_WAIT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAND_ROW_ADDR_3 ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 int nand_fill_column_cycles (struct nand_chip*,unsigned int*,unsigned int) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nand_lp_exec_read_page_op(struct nand_chip *chip, unsigned int page,
				     unsigned int offset_in_page, void *buf,
				     unsigned int len)
{
	const struct nand_sdr_timings *sdr =
		nand_get_sdr_timings(&chip->data_interface);
	u8 addrs[5];
	struct nand_op_instr instrs[] = {
		NAND_OP_CMD(NAND_CMD_READ0, 0),
		NAND_OP_ADDR(4, addrs, 0),
		NAND_OP_CMD(NAND_CMD_READSTART, PSEC_TO_NSEC(sdr->tWB_max)),
		NAND_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tR_max),
				 PSEC_TO_NSEC(sdr->tRR_min)),
		NAND_OP_DATA_IN(len, buf, 0),
	};
	struct nand_operation op = NAND_OPERATION(chip->cur_cs, instrs);
	int ret;

	/* Drop the DATA_IN instruction if len is set to 0. */
	if (!len)
		op.ninstrs--;

	ret = nand_fill_column_cycles(chip, addrs, offset_in_page);
	if (ret < 0)
		return ret;

	addrs[2] = page;
	addrs[3] = page >> 8;

	if (chip->options & NAND_ROW_ADDR_3) {
		addrs[4] = page >> 16;
		instrs[1].ctx.addr.naddrs++;
	}

	return nand_exec_op(chip, &op);
}