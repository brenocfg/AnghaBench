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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct nfp_insn_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  BR_BLO ; 
 int /*<<< orphan*/  BR_OFF_RELO ; 
 int /*<<< orphan*/  RELO_BR_GO_ABORT ; 
 int data_ld (struct nfp_prog*,struct nfp_insn_meta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  plen_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  re_load_imm_any (struct nfp_prog*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
construct_data_ld(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		  u16 offset, u8 size)
{
	swreg tmp_reg;

	/* Check packet length */
	tmp_reg = ur_load_imm_any(nfp_prog, offset + size, imm_a(nfp_prog));
	emit_alu(nfp_prog, reg_none(), plen_reg(nfp_prog), ALU_OP_SUB, tmp_reg);
	emit_br_relo(nfp_prog, BR_BLO, BR_OFF_RELO, 0, RELO_BR_GO_ABORT);

	/* Load data */
	tmp_reg = re_load_imm_any(nfp_prog, offset, imm_b(nfp_prog));
	return data_ld(nfp_prog, meta, tmp_reg, 0, size);
}