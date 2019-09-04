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
struct TYPE_11__ {unsigned int timeout_ms; } ;
struct TYPE_9__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; TYPE_3__ buf; int /*<<< orphan*/  force_8bit; } ;
struct TYPE_8__ {unsigned int naddrs; unsigned int* addrs; } ;
struct TYPE_7__ {unsigned int opcode; } ;
struct TYPE_12__ {TYPE_5__ waitrdy; TYPE_4__ data; TYPE_2__ addr; TYPE_1__ cmd; } ;
struct nand_op_instr {int type; TYPE_6__ ctx; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct fsmc_nand_data {int /*<<< orphan*/  mode; int /*<<< orphan*/  addr_va; int /*<<< orphan*/  cmd_va; } ;

/* Variables and functions */
#define  NAND_OP_ADDR_INSTR 132 
#define  NAND_OP_CMD_INSTR 131 
#define  NAND_OP_DATA_IN_INSTR 130 
#define  NAND_OP_DATA_OUT_INSTR 129 
#define  NAND_OP_WAITRDY_INSTR 128 
 int /*<<< orphan*/  USE_DMA_ACCESS ; 
 int /*<<< orphan*/  fsmc_read_buf (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsmc_read_buf_dma (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsmc_write_buf (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsmc_write_buf_dma (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsmc_nand_data* mtd_to_fsmc (struct mtd_info*) ; 
 int nand_soft_waitrdy (struct nand_chip*,unsigned int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,...) ; 
 int /*<<< orphan*/  writeb_relaxed (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsmc_exec_op(struct nand_chip *chip, const struct nand_operation *op,
			bool check_only)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct fsmc_nand_data *host = mtd_to_fsmc(mtd);
	const struct nand_op_instr *instr = NULL;
	int ret = 0;
	unsigned int op_id;
	int i;

	pr_debug("Executing operation [%d instructions]:\n", op->ninstrs);
	for (op_id = 0; op_id < op->ninstrs; op_id++) {
		instr = &op->instrs[op_id];

		switch (instr->type) {
		case NAND_OP_CMD_INSTR:
			pr_debug("  ->CMD      [0x%02x]\n",
				 instr->ctx.cmd.opcode);

			writeb_relaxed(instr->ctx.cmd.opcode, host->cmd_va);
			break;

		case NAND_OP_ADDR_INSTR:
			pr_debug("  ->ADDR     [%d cyc]",
				 instr->ctx.addr.naddrs);

			for (i = 0; i < instr->ctx.addr.naddrs; i++)
				writeb_relaxed(instr->ctx.addr.addrs[i],
					       host->addr_va);
			break;

		case NAND_OP_DATA_IN_INSTR:
			pr_debug("  ->DATA_IN  [%d B%s]\n", instr->ctx.data.len,
				 instr->ctx.data.force_8bit ?
				 ", force 8-bit" : "");

			if (host->mode == USE_DMA_ACCESS)
				fsmc_read_buf_dma(mtd, instr->ctx.data.buf.in,
						  instr->ctx.data.len);
			else
				fsmc_read_buf(mtd, instr->ctx.data.buf.in,
					      instr->ctx.data.len);
			break;

		case NAND_OP_DATA_OUT_INSTR:
			pr_debug("  ->DATA_OUT [%d B%s]\n", instr->ctx.data.len,
				 instr->ctx.data.force_8bit ?
				 ", force 8-bit" : "");

			if (host->mode == USE_DMA_ACCESS)
				fsmc_write_buf_dma(mtd, instr->ctx.data.buf.out,
						   instr->ctx.data.len);
			else
				fsmc_write_buf(mtd, instr->ctx.data.buf.out,
					       instr->ctx.data.len);
			break;

		case NAND_OP_WAITRDY_INSTR:
			pr_debug("  ->WAITRDY  [max %d ms]\n",
				 instr->ctx.waitrdy.timeout_ms);

			ret = nand_soft_waitrdy(chip,
						instr->ctx.waitrdy.timeout_ms);
			break;
		}
	}

	return ret;
}