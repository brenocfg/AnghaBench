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
typedef  int u8 ;
typedef  int u64 ;
struct nfp_prog {int dummy; } ;
typedef  enum cmd_tgt_map { ____Placeholder_cmd_tgt_map } cmd_tgt_map ;
typedef  enum cmd_ctx_swap { ____Placeholder_cmd_ctx_swap } cmd_ctx_swap ;
struct TYPE_2__ {int token; int tgt_cmd; } ;

/* Variables and functions */
 int CMD_CTX_NO_SWAP ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_CMD_A_SRC ; 
 int /*<<< orphan*/  OP_CMD_B_SRC ; 
 int /*<<< orphan*/  OP_CMD_CNT ; 
 int /*<<< orphan*/  OP_CMD_CTX ; 
 int /*<<< orphan*/  OP_CMD_INDIR ; 
 int /*<<< orphan*/  OP_CMD_MODE ; 
 int /*<<< orphan*/  OP_CMD_SIG ; 
 int /*<<< orphan*/  OP_CMD_TGT_CMD ; 
 int /*<<< orphan*/  OP_CMD_TOKEN ; 
 int /*<<< orphan*/  OP_CMD_XFER ; 
 TYPE_1__* cmd_tgt_act ; 
 int /*<<< orphan*/  nfp_prog_push (struct nfp_prog*,int) ; 

__attribute__((used)) static void
__emit_cmd(struct nfp_prog *nfp_prog, enum cmd_tgt_map op,
	   u8 mode, u8 xfer, u8 areg, u8 breg, u8 size, enum cmd_ctx_swap ctx,
	   bool indir)
{
	u64 insn;

	insn =	FIELD_PREP(OP_CMD_A_SRC, areg) |
		FIELD_PREP(OP_CMD_CTX, ctx) |
		FIELD_PREP(OP_CMD_B_SRC, breg) |
		FIELD_PREP(OP_CMD_TOKEN, cmd_tgt_act[op].token) |
		FIELD_PREP(OP_CMD_XFER, xfer) |
		FIELD_PREP(OP_CMD_CNT, size) |
		FIELD_PREP(OP_CMD_SIG, ctx != CMD_CTX_NO_SWAP) |
		FIELD_PREP(OP_CMD_TGT_CMD, cmd_tgt_act[op].tgt_cmd) |
		FIELD_PREP(OP_CMD_INDIR, indir) |
		FIELD_PREP(OP_CMD_MODE, mode);

	nfp_prog_push(nfp_prog, insn);
}