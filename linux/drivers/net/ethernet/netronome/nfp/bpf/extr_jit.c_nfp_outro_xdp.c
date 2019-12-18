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
struct nfp_prog {void* tgt_abort; void* tgt_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_OR ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  BR_BLO ; 
 int /*<<< orphan*/  BR_OFF_RELO ; 
 int /*<<< orphan*/  BR_UNC ; 
 int /*<<< orphan*/  NFP_BPF_ABI_FLAGS ; 
 int /*<<< orphan*/  RELO_BR_NEXT_PKT ; 
 int /*<<< orphan*/  SHF_OP_AND ; 
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_L_SHF ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_ld_field (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_imm (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_outro_xdp(struct nfp_prog *nfp_prog)
{
	/* XDP return codes:
	 *   0 aborted  0x82 -> drop,  count as stat3
	 *   1    drop  0x22 -> drop,  count as stat1
	 *   2    pass  0x11 -> pass,  count as stat0
	 *   3      tx  0x44 -> redir, count as stat2
	 *   * unknown  0x82 -> drop,  count as stat3
	 */
	/* Target for aborts */
	nfp_prog->tgt_abort = nfp_prog_current_offset(nfp_prog);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2, RELO_BR_NEXT_PKT);

	wrp_mov(nfp_prog, reg_a(0), NFP_BPF_ABI_FLAGS);
	emit_ld_field(nfp_prog, reg_a(0), 0xc, reg_imm(0x82), SHF_SC_L_SHF, 16);

	/* Target for normal exits */
	nfp_prog->tgt_out = nfp_prog_current_offset(nfp_prog);

	/* if R0 > 3 jump to abort */
	emit_alu(nfp_prog, reg_none(), reg_imm(3), ALU_OP_SUB, reg_b(0));
	emit_br(nfp_prog, BR_BLO, nfp_prog->tgt_abort, 0);

	wrp_immed(nfp_prog, reg_b(2), 0x44112282);

	emit_shf(nfp_prog, reg_a(1),
		 reg_none(), SHF_OP_NONE, reg_b(0), SHF_SC_L_SHF, 3);

	emit_alu(nfp_prog, reg_none(), reg_a(1), ALU_OP_OR, reg_imm(0));
	emit_shf(nfp_prog, reg_b(2),
		 reg_imm(0xff), SHF_OP_AND, reg_b(2), SHF_SC_R_SHF, 0);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2, RELO_BR_NEXT_PKT);

	wrp_mov(nfp_prog, reg_a(0), NFP_BPF_ABI_FLAGS);
	emit_ld_field(nfp_prog, reg_a(0), 0xc, reg_b(2), SHF_SC_L_SHF, 16);
}