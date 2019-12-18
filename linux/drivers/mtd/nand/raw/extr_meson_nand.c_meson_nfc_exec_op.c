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
typedef  size_t u32 ;
struct nand_operation {size_t ninstrs; struct nand_op_instr* instrs; int /*<<< orphan*/  cs; } ;
struct TYPE_11__ {int /*<<< orphan*/  timeout_ms; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; } ;
struct TYPE_9__ {int naddrs; int* addrs; } ;
struct TYPE_7__ {int opcode; } ;
struct TYPE_12__ {TYPE_5__ waitrdy; TYPE_4__ data; TYPE_3__ addr; TYPE_1__ cmd; } ;
struct nand_op_instr {int type; int /*<<< orphan*/  delay_ns; TYPE_6__ ctx; } ;
struct nand_chip {int dummy; } ;
struct meson_nfc_nand_chip {int level1_divider; } ;
struct TYPE_8__ {size_t chip_select; } ;
struct meson_nfc {scalar_t__ reg_base; TYPE_2__ param; } ;

/* Variables and functions */
 size_t DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
#define  NAND_OP_ADDR_INSTR 132 
#define  NAND_OP_CMD_INSTR 131 
#define  NAND_OP_DATA_IN_INSTR 130 
#define  NAND_OP_DATA_OUT_INSTR 129 
#define  NAND_OP_WAITRDY_INSTR 128 
 int NFC_CLK_CYCLE ; 
 size_t NFC_CMD_ALE ; 
 size_t NFC_CMD_CLE ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 void* meson_nand_op_get_dma_safe_input_buf (struct nand_op_instr const*) ; 
 void* meson_nand_op_get_dma_safe_output_buf (struct nand_op_instr const*) ; 
 int /*<<< orphan*/  meson_nand_op_put_dma_safe_input_buf (struct nand_op_instr const*,void*) ; 
 int /*<<< orphan*/  meson_nand_op_put_dma_safe_output_buf (struct nand_op_instr const*,void*) ; 
 int /*<<< orphan*/  meson_nfc_cmd_idle (struct meson_nfc*,size_t) ; 
 int /*<<< orphan*/  meson_nfc_queue_rb (struct meson_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_nfc_read_buf (struct nand_chip*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_nfc_select_chip (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_nfc_wait_cmd_finish (struct meson_nfc*,int) ; 
 int /*<<< orphan*/  meson_nfc_write_buf (struct nand_chip*,void*,int /*<<< orphan*/ ) ; 
 struct meson_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct meson_nfc_nand_chip* to_meson_nand (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int meson_nfc_exec_op(struct nand_chip *nand,
			     const struct nand_operation *op, bool check_only)
{
	struct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	struct meson_nfc *nfc = nand_get_controller_data(nand);
	const struct nand_op_instr *instr = NULL;
	void *buf;
	u32 op_id, delay_idle, cmd;
	int i;

	meson_nfc_select_chip(nand, op->cs);
	for (op_id = 0; op_id < op->ninstrs; op_id++) {
		instr = &op->instrs[op_id];
		delay_idle = DIV_ROUND_UP(PSEC_TO_NSEC(instr->delay_ns),
					  meson_chip->level1_divider *
					  NFC_CLK_CYCLE);
		switch (instr->type) {
		case NAND_OP_CMD_INSTR:
			cmd = nfc->param.chip_select | NFC_CMD_CLE;
			cmd |= instr->ctx.cmd.opcode & 0xff;
			writel(cmd, nfc->reg_base + NFC_REG_CMD);
			meson_nfc_cmd_idle(nfc, delay_idle);
			break;

		case NAND_OP_ADDR_INSTR:
			for (i = 0; i < instr->ctx.addr.naddrs; i++) {
				cmd = nfc->param.chip_select | NFC_CMD_ALE;
				cmd |= instr->ctx.addr.addrs[i] & 0xff;
				writel(cmd, nfc->reg_base + NFC_REG_CMD);
			}
			meson_nfc_cmd_idle(nfc, delay_idle);
			break;

		case NAND_OP_DATA_IN_INSTR:
			buf = meson_nand_op_get_dma_safe_input_buf(instr);
			if (!buf)
				return -ENOMEM;
			meson_nfc_read_buf(nand, buf, instr->ctx.data.len);
			meson_nand_op_put_dma_safe_input_buf(instr, buf);
			break;

		case NAND_OP_DATA_OUT_INSTR:
			buf = meson_nand_op_get_dma_safe_output_buf(instr);
			if (!buf)
				return -ENOMEM;
			meson_nfc_write_buf(nand, buf, instr->ctx.data.len);
			meson_nand_op_put_dma_safe_output_buf(instr, buf);
			break;

		case NAND_OP_WAITRDY_INSTR:
			meson_nfc_queue_rb(nfc, instr->ctx.waitrdy.timeout_ms);
			if (instr->delay_ns)
				meson_nfc_cmd_idle(nfc, delay_idle);
			break;
		}
	}
	meson_nfc_wait_cmd_finish(nfc, 1000);
	return 0;
}