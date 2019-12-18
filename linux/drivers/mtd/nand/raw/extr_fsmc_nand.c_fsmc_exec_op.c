#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nand_operation {unsigned int ninstrs; struct nand_op_instr* instrs; } ;
struct TYPE_11__ {int /*<<< orphan*/  timeout_ms; } ;
struct TYPE_9__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; TYPE_3__ buf; } ;
struct TYPE_8__ {int naddrs; int /*<<< orphan*/ * addrs; } ;
struct TYPE_7__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {TYPE_5__ waitrdy; TYPE_4__ data; TYPE_2__ addr; TYPE_1__ cmd; } ;
struct nand_op_instr {int type; TYPE_6__ ctx; } ;
struct nand_chip {int dummy; } ;
struct fsmc_nand_data {int /*<<< orphan*/  mode; int /*<<< orphan*/  addr_va; int /*<<< orphan*/  cmd_va; } ;

/* Variables and functions */
#define  NAND_OP_ADDR_INSTR 132 
#define  NAND_OP_CMD_INSTR 131 
#define  NAND_OP_DATA_IN_INSTR 130 
#define  NAND_OP_DATA_OUT_INSTR 129 
#define  NAND_OP_WAITRDY_INSTR 128 
 int /*<<< orphan*/  USE_DMA_ACCESS ; 
 int /*<<< orphan*/  fsmc_read_buf (struct fsmc_nand_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsmc_read_buf_dma (struct fsmc_nand_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsmc_write_buf (struct fsmc_nand_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsmc_write_buf_dma (struct fsmc_nand_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_op_trace (char*,struct nand_op_instr const*) ; 
 int nand_soft_waitrdy (struct nand_chip*,int /*<<< orphan*/ ) ; 
 struct fsmc_nand_data* nand_to_fsmc (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  writeb_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsmc_exec_op(struct nand_chip *chip, const struct nand_operation *op,
			bool check_only)
{
	struct fsmc_nand_data *host = nand_to_fsmc(chip);
	const struct nand_op_instr *instr = NULL;
	int ret = 0;
	unsigned int op_id;
	int i;

	pr_debug("Executing operation [%d instructions]:\n", op->ninstrs);

	for (op_id = 0; op_id < op->ninstrs; op_id++) {
		instr = &op->instrs[op_id];

		nand_op_trace("  ", instr);

		switch (instr->type) {
		case NAND_OP_CMD_INSTR:
			writeb_relaxed(instr->ctx.cmd.opcode, host->cmd_va);
			break;

		case NAND_OP_ADDR_INSTR:
			for (i = 0; i < instr->ctx.addr.naddrs; i++)
				writeb_relaxed(instr->ctx.addr.addrs[i],
					       host->addr_va);
			break;

		case NAND_OP_DATA_IN_INSTR:
			if (host->mode == USE_DMA_ACCESS)
				fsmc_read_buf_dma(host, instr->ctx.data.buf.in,
						  instr->ctx.data.len);
			else
				fsmc_read_buf(host, instr->ctx.data.buf.in,
					      instr->ctx.data.len);
			break;

		case NAND_OP_DATA_OUT_INSTR:
			if (host->mode == USE_DMA_ACCESS)
				fsmc_write_buf_dma(host,
						   instr->ctx.data.buf.out,
						   instr->ctx.data.len);
			else
				fsmc_write_buf(host, instr->ctx.data.buf.out,
					       instr->ctx.data.len);
			break;

		case NAND_OP_WAITRDY_INSTR:
			ret = nand_soft_waitrdy(chip,
						instr->ctx.waitrdy.timeout_ms);
			break;
		}
	}

	return ret;
}