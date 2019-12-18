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
typedef  int u8 ;
struct nand_sdr_timings {int /*<<< orphan*/  tPROG_max; int /*<<< orphan*/  tWB_max; int /*<<< orphan*/  tADL_min; } ;
struct nand_operation {scalar_t__ ninstrs; int /*<<< orphan*/  instrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int naddrs; } ;
struct TYPE_6__ {TYPE_2__ cmd; TYPE_1__ addr; } ;
struct nand_op_instr {TYPE_3__ ctx; } ;
struct nand_chip {int options; int /*<<< orphan*/  cur_cs; int /*<<< orphan*/  data_interface; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int /*<<< orphan*/  NAND_CMD_READ1 ; 
 int /*<<< orphan*/  NAND_CMD_READOOB ; 
 int /*<<< orphan*/  NAND_CMD_SEQIN ; 
 struct nand_operation NAND_OPERATION (int /*<<< orphan*/ ,struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_ADDR (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_DATA_OUT (unsigned int,void const*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_WAIT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAND_ROW_ADDR_3 ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 int nand_fill_column_cycles (struct nand_chip*,int*,unsigned int) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 int nand_status_op (struct nand_chip*,int*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int nand_exec_prog_page_op(struct nand_chip *chip, unsigned int page,
				  unsigned int offset_in_page, const void *buf,
				  unsigned int len, bool prog)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct nand_sdr_timings *sdr =
		nand_get_sdr_timings(&chip->data_interface);
	u8 addrs[5] = {};
	struct nand_op_instr instrs[] = {
		/*
		 * The first instruction will be dropped if we're dealing
		 * with a large page NAND and adjusted if we're dealing
		 * with a small page NAND and the page offset is > 255.
		 */
		NAND_OP_CMD(NAND_CMD_READ0, 0),
		NAND_OP_CMD(NAND_CMD_SEQIN, 0),
		NAND_OP_ADDR(0, addrs, PSEC_TO_NSEC(sdr->tADL_min)),
		NAND_OP_DATA_OUT(len, buf, 0),
		NAND_OP_CMD(NAND_CMD_PAGEPROG, PSEC_TO_NSEC(sdr->tWB_max)),
		NAND_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tPROG_max), 0),
	};
	struct nand_operation op = NAND_OPERATION(chip->cur_cs, instrs);
	int naddrs = nand_fill_column_cycles(chip, addrs, offset_in_page);
	int ret;
	u8 status;

	if (naddrs < 0)
		return naddrs;

	addrs[naddrs++] = page;
	addrs[naddrs++] = page >> 8;
	if (chip->options & NAND_ROW_ADDR_3)
		addrs[naddrs++] = page >> 16;

	instrs[2].ctx.addr.naddrs = naddrs;

	/* Drop the last two instructions if we're not programming the page. */
	if (!prog) {
		op.ninstrs -= 2;
		/* Also drop the DATA_OUT instruction if empty. */
		if (!len)
			op.ninstrs--;
	}

	if (mtd->writesize <= 512) {
		/*
		 * Small pages need some more tweaking: we have to adjust the
		 * first instruction depending on the page offset we're trying
		 * to access.
		 */
		if (offset_in_page >= mtd->writesize)
			instrs[0].ctx.cmd.opcode = NAND_CMD_READOOB;
		else if (offset_in_page >= 256 &&
			 !(chip->options & NAND_BUSWIDTH_16))
			instrs[0].ctx.cmd.opcode = NAND_CMD_READ1;
	} else {
		/*
		 * Drop the first command if we're dealing with a large page
		 * NAND.
		 */
		op.instrs++;
		op.ninstrs--;
	}

	ret = nand_exec_op(chip, &op);
	if (!prog || ret)
		return ret;

	ret = nand_status_op(chip, &status);
	if (ret)
		return ret;

	return status;
}