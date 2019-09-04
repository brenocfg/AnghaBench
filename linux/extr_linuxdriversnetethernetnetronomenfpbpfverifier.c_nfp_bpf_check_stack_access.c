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
struct nfp_prog {int dummy; } ;
struct TYPE_4__ {int value; } ;
struct TYPE_5__ {scalar_t__ type; int off; TYPE_1__ var_off; } ;
struct nfp_insn_meta {int ptr_not_const; TYPE_2__ ptr; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_6__ {int value; } ;
struct bpf_reg_state {int off; TYPE_3__ var_off; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NOT_INIT ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,...) ; 
 int /*<<< orphan*/  tnum_is_const (TYPE_3__) ; 

__attribute__((used)) static int
nfp_bpf_check_stack_access(struct nfp_prog *nfp_prog,
			   struct nfp_insn_meta *meta,
			   const struct bpf_reg_state *reg,
			   struct bpf_verifier_env *env)
{
	s32 old_off, new_off;

	if (!tnum_is_const(reg->var_off)) {
		pr_vlog(env, "variable ptr stack access\n");
		return -EINVAL;
	}

	if (meta->ptr.type == NOT_INIT)
		return 0;

	old_off = meta->ptr.off + meta->ptr.var_off.value;
	new_off = reg->off + reg->var_off.value;

	meta->ptr_not_const |= old_off != new_off;

	if (!meta->ptr_not_const)
		return 0;

	if (old_off % 4 == new_off % 4)
		return 0;

	pr_vlog(env, "stack access changed location was:%d is:%d\n",
		old_off, new_off);
	return -EINVAL;
}