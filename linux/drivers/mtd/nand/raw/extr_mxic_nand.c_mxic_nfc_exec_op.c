#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nand_operation {unsigned int ninstrs; struct nand_op_instr* instrs; } ;
struct TYPE_8__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
struct TYPE_9__ {int len; TYPE_3__ buf; } ;
struct TYPE_7__ {int naddrs; int /*<<< orphan*/ * addrs; } ;
struct TYPE_6__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {TYPE_4__ data; TYPE_2__ addr; TYPE_1__ cmd; } ;
struct nand_op_instr {int type; TYPE_5__ ctx; } ;
struct nand_chip {int dummy; } ;
struct mxic_nand_ctlr {scalar_t__ regs; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 scalar_t__ HC_EN ; 
 int HC_EN_BIT ; 
#define  NAND_OP_ADDR_INSTR 132 
#define  NAND_OP_CMD_INSTR 131 
#define  NAND_OP_DATA_IN_INSTR 130 
#define  NAND_OP_DATA_OUT_INSTR 129 
#define  NAND_OP_WAITRDY_INSTR 128 
 scalar_t__ ONFI_DIN_CNT (int /*<<< orphan*/ ) ; 
 int OP_ADDR_BUSW (int /*<<< orphan*/ ) ; 
 int OP_ADDR_BYTES (int) ; 
 int /*<<< orphan*/  OP_BUSW_8 ; 
 int OP_CMD_BUSW (int /*<<< orphan*/ ) ; 
 int OP_CMD_BYTES (int /*<<< orphan*/ ) ; 
 int OP_DATA_BUSW (int /*<<< orphan*/ ) ; 
 int OP_DUMMY_CYC (int) ; 
 int OP_READ ; 
 scalar_t__ SS_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxic_nfc_cs_disable (struct mxic_nand_ctlr*) ; 
 int /*<<< orphan*/  mxic_nfc_cs_enable (struct mxic_nand_ctlr*) ; 
 int mxic_nfc_data_xfer (struct mxic_nand_ctlr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mxic_nfc_wait_ready (struct nand_chip*) ; 
 struct mxic_nand_ctlr* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxic_nfc_exec_op(struct nand_chip *chip,
			    const struct nand_operation *op, bool check_only)
{
	struct mxic_nand_ctlr *nfc = nand_get_controller_data(chip);
	const struct nand_op_instr *instr = NULL;
	int ret = 0;
	unsigned int op_id;

	mxic_nfc_cs_enable(nfc);
	init_completion(&nfc->complete);
	for (op_id = 0; op_id < op->ninstrs; op_id++) {
		instr = &op->instrs[op_id];

		switch (instr->type) {
		case NAND_OP_CMD_INSTR:
			writel(0, nfc->regs + HC_EN);
			writel(HC_EN_BIT, nfc->regs + HC_EN);
			writel(OP_CMD_BUSW(OP_BUSW_8) |  OP_DUMMY_CYC(0x3F) |
			       OP_CMD_BYTES(0), nfc->regs + SS_CTRL(0));

			ret = mxic_nfc_data_xfer(nfc,
						 &instr->ctx.cmd.opcode,
						 NULL, 1);
			break;

		case NAND_OP_ADDR_INSTR:
			writel(OP_ADDR_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F) |
			       OP_ADDR_BYTES(instr->ctx.addr.naddrs),
			       nfc->regs + SS_CTRL(0));
			ret = mxic_nfc_data_xfer(nfc,
						 instr->ctx.addr.addrs, NULL,
						 instr->ctx.addr.naddrs);
			break;

		case NAND_OP_DATA_IN_INSTR:
			writel(0x0, nfc->regs + ONFI_DIN_CNT(0));
			writel(OP_DATA_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F) |
			       OP_READ, nfc->regs + SS_CTRL(0));
			ret = mxic_nfc_data_xfer(nfc, NULL,
						 instr->ctx.data.buf.in,
						 instr->ctx.data.len);
			break;

		case NAND_OP_DATA_OUT_INSTR:
			writel(instr->ctx.data.len,
			       nfc->regs + ONFI_DIN_CNT(0));
			writel(OP_DATA_BUSW(OP_BUSW_8) | OP_DUMMY_CYC(0x3F),
			       nfc->regs + SS_CTRL(0));
			ret = mxic_nfc_data_xfer(nfc,
						 instr->ctx.data.buf.out, NULL,
						 instr->ctx.data.len);
			break;

		case NAND_OP_WAITRDY_INSTR:
			ret = mxic_nfc_wait_ready(chip);
			break;
		}
	}
	mxic_nfc_cs_disable(nfc);

	return ret;
}