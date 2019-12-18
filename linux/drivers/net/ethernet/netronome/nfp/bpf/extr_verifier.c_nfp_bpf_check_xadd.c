#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfp_prog {int dummy; } ;
struct TYPE_4__ {int src_reg; int dst_reg; } ;
struct nfp_insn_meta {int xadd_over_16bit; int xadd_maybe_16bit; TYPE_2__ insn; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_3__ {int value; int mask; } ;
struct bpf_reg_state {scalar_t__ type; TYPE_1__ var_off; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ PTR_TO_MAP_VALUE ; 
 scalar_t__ SCALAR_VALUE ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int nfp_bpf_check_ptr (struct nfp_prog*,struct nfp_insn_meta*,struct bpf_verifier_env*,int) ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,scalar_t__) ; 

__attribute__((used)) static int
nfp_bpf_check_xadd(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		   struct bpf_verifier_env *env)
{
	const struct bpf_reg_state *sreg = cur_regs(env) + meta->insn.src_reg;
	const struct bpf_reg_state *dreg = cur_regs(env) + meta->insn.dst_reg;

	if (dreg->type != PTR_TO_MAP_VALUE) {
		pr_vlog(env, "atomic add not to a map value pointer: %d\n",
			dreg->type);
		return -EOPNOTSUPP;
	}
	if (sreg->type != SCALAR_VALUE) {
		pr_vlog(env, "atomic add not of a scalar: %d\n", sreg->type);
		return -EOPNOTSUPP;
	}

	meta->xadd_over_16bit |=
		sreg->var_off.value > 0xffff || sreg->var_off.mask > 0xffff;
	meta->xadd_maybe_16bit |=
		(sreg->var_off.value & ~sreg->var_off.mask) <= 0xffff;

	return nfp_bpf_check_ptr(nfp_prog, meta, env, meta->insn.dst_reg);
}