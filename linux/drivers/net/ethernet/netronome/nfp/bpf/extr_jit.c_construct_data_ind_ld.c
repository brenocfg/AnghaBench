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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  BR_BLO ; 
 int /*<<< orphan*/  BR_OFF_RELO ; 
 int /*<<< orphan*/  RELO_BR_GO_ABORT ; 
 int data_ld (struct nfp_prog*,struct nfp_insn_meta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_both (struct nfp_prog*) ; 
 int /*<<< orphan*/  plen_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
construct_data_ind_ld(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		      u16 offset, u16 src, u8 size)
{
	swreg tmp_reg;

	/* Calculate the true offset (src_reg + imm) */
	tmp_reg = ur_load_imm_any(nfp_prog, offset, imm_b(nfp_prog));
	emit_alu(nfp_prog, imm_both(nfp_prog), reg_a(src), ALU_OP_ADD, tmp_reg);

	/* Check packet length (size guaranteed to fit b/c it's u8) */
	emit_alu(nfp_prog, imm_a(nfp_prog),
		 imm_a(nfp_prog), ALU_OP_ADD, reg_imm(size));
	emit_alu(nfp_prog, reg_none(),
		 plen_reg(nfp_prog), ALU_OP_SUB, imm_a(nfp_prog));
	emit_br_relo(nfp_prog, BR_BLO, BR_OFF_RELO, 0, RELO_BR_GO_ABORT);

	/* Load data */
	return data_ld(nfp_prog, meta, imm_b(nfp_prog), 0, size);
}