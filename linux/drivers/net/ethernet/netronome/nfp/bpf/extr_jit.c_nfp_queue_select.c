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
typedef  scalar_t__ u32 ;
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int src_reg; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_AND_NOT_B ; 
 int /*<<< orphan*/  BR_BEQ ; 
 int EINVAL ; 
 int NFP_NET_RXR_MAX ; 
 int /*<<< orphan*/  PKT_VEL_QSEL_SET_BIT ; 
 int /*<<< orphan*/  SHF_OP_OR ; 
 int /*<<< orphan*/  SHF_SC_L_SHF ; 
 int /*<<< orphan*/  SHF_SC_NONE ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_ld_field (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,scalar_t__) ; 
 scalar_t__ nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  pv_qsel_set (struct nfp_prog*) ; 
 int /*<<< orphan*/  pv_qsel_val (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_imm (int) ; 
 int /*<<< orphan*/  reg_none () ; 

__attribute__((used)) static int
nfp_queue_select(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	u32 jmp_tgt;

	jmp_tgt = nfp_prog_current_offset(nfp_prog) + 5;

	/* Make sure the queue id fits into FW field */
	emit_alu(nfp_prog, reg_none(), reg_a(meta->insn.src_reg * 2),
		 ALU_OP_AND_NOT_B, reg_imm(0xff));
	emit_br(nfp_prog, BR_BEQ, jmp_tgt, 2);

	/* Set the 'queue selected' bit and the queue value */
	emit_shf(nfp_prog, pv_qsel_set(nfp_prog),
		 pv_qsel_set(nfp_prog), SHF_OP_OR, reg_imm(1),
		 SHF_SC_L_SHF, PKT_VEL_QSEL_SET_BIT);
	emit_ld_field(nfp_prog,
		      pv_qsel_val(nfp_prog), 0x1, reg_b(meta->insn.src_reg * 2),
		      SHF_SC_NONE, 0);
	/* Delay slots end here, we will jump over next instruction if queue
	 * value fits into the field.
	 */
	emit_ld_field(nfp_prog,
		      pv_qsel_val(nfp_prog), 0x1, reg_imm(NFP_NET_RXR_MAX),
		      SHF_SC_NONE, 0);

	if (!nfp_prog_confirm_current_offset(nfp_prog, jmp_tgt))
		return -EINVAL;

	return 0;
}