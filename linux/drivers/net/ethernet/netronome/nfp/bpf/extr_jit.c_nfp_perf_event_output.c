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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct nfp_insn_meta {scalar_t__ func_id; TYPE_1__ arg1; } ;

/* Variables and functions */
 scalar_t__ BR_OFF_RELO ; 
 int /*<<< orphan*/  BR_UNC ; 
 int EINVAL ; 
 int /*<<< orphan*/  RELO_BR_HELPER ; 
 int /*<<< orphan*/  RELO_IMMED_REL ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,scalar_t__) ; 
 scalar_t__ nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed_relo (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_perf_event_output(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	swreg ptr_type;
	u32 ret_tgt;

	ptr_type = ur_load_imm_any(nfp_prog, meta->arg1.type, imm_a(nfp_prog));

	ret_tgt = nfp_prog_current_offset(nfp_prog) + 3;

	emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO + meta->func_id,
		     2, RELO_BR_HELPER);

	/* Load ptr type into A1 */
	wrp_mov(nfp_prog, reg_a(1), ptr_type);

	/* Load the return address into B0 */
	wrp_immed_relo(nfp_prog, reg_b(0), ret_tgt, RELO_IMMED_REL);

	if (!nfp_prog_confirm_current_offset(nfp_prog, ret_tgt))
		return -EINVAL;

	return 0;
}