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
typedef  scalar_t__ u32 ;
struct nfp_prog {scalar_t__ stack_frame_depth; } ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_5__ {scalar_t__ off; TYPE_1__ var_off; } ;
struct TYPE_6__ {scalar_t__ var_off; TYPE_2__ reg; } ;
struct nfp_insn_meta {scalar_t__ func_id; TYPE_3__ arg2; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ BPF_FUNC_map_update_elem ; 
 scalar_t__ BR_OFF_RELO ; 
 int /*<<< orphan*/  BR_UNC ; 
 int EINVAL ; 
 int /*<<< orphan*/  NFP_CSR_ACT_LM_ADDR0 ; 
 int /*<<< orphan*/  NFP_CSR_ACT_LM_ADDR2 ; 
 int /*<<< orphan*/  RELO_BR_HELPER ; 
 int /*<<< orphan*/  RELO_IMMED_REL ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_csr_wr (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,scalar_t__) ; 
 scalar_t__ nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  stack_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  wrp_immed_relo (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_nops (struct nfp_prog*,int) ; 

__attribute__((used)) static int
map_call_stack_common(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	bool load_lm_ptr;
	u32 ret_tgt;
	s64 lm_off;

	/* We only have to reload LM0 if the key is not at start of stack */
	lm_off = nfp_prog->stack_frame_depth;
	lm_off += meta->arg2.reg.var_off.value + meta->arg2.reg.off;
	load_lm_ptr = meta->arg2.var_off || lm_off;

	/* Set LM0 to start of key */
	if (load_lm_ptr)
		emit_csr_wr(nfp_prog, reg_b(2 * 2), NFP_CSR_ACT_LM_ADDR0);
	if (meta->func_id == BPF_FUNC_map_update_elem)
		emit_csr_wr(nfp_prog, reg_b(3 * 2), NFP_CSR_ACT_LM_ADDR2);

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO + meta->func_id,
		     2, RELO_BR_HELPER);
	ret_tgt = nfp_prog_current_offset(nfp_prog) + 2;

	/* Load map ID into A0 */
	wrp_mov(nfp_prog, reg_a(0), reg_a(2));

	/* Load the return address into B0 */
	wrp_immed_relo(nfp_prog, reg_b(0), ret_tgt, RELO_IMMED_REL);

	if (!nfp_prog_confirm_current_offset(nfp_prog, ret_tgt))
		return -EINVAL;

	/* Reset the LM0 pointer */
	if (!load_lm_ptr)
		return 0;

	emit_csr_wr(nfp_prog, stack_reg(nfp_prog), NFP_CSR_ACT_LM_ADDR0);
	wrp_nops(nfp_prog, 3);

	return 0;
}