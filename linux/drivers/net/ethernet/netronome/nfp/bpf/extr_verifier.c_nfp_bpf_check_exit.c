#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char* u64 ;
typedef  int /*<<< orphan*/  tn_buf ;
struct nfp_prog {scalar_t__ type; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_3__ {char* value; } ;
struct bpf_reg_state {scalar_t__ type; TYPE_1__ var_off; } ;

/* Variables and functions */
 scalar_t__ BPF_PROG_TYPE_SCHED_CLS ; 
 scalar_t__ BPF_PROG_TYPE_XDP ; 
 int BPF_REG_0 ; 
 int EINVAL ; 
 scalar_t__ SCALAR_VALUE ; 
 char* TC_ACT_QUEUED ; 
 char* TC_ACT_REDIRECT ; 
 char* TC_ACT_SHOT ; 
 char* TC_ACT_STOLEN ; 
 struct bpf_reg_state* cur_regs (struct bpf_verifier_env*) ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,scalar_t__,char*) ; 
 scalar_t__ tnum_is_const (TYPE_1__) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,TYPE_1__) ; 

__attribute__((used)) static int
nfp_bpf_check_exit(struct nfp_prog *nfp_prog,
		   struct bpf_verifier_env *env)
{
	const struct bpf_reg_state *reg0 = cur_regs(env) + BPF_REG_0;
	u64 imm;

	if (nfp_prog->type == BPF_PROG_TYPE_XDP)
		return 0;

	if (!(reg0->type == SCALAR_VALUE && tnum_is_const(reg0->var_off))) {
		char tn_buf[48];

		tnum_strn(tn_buf, sizeof(tn_buf), reg0->var_off);
		pr_vlog(env, "unsupported exit state: %d, var_off: %s\n",
			reg0->type, tn_buf);
		return -EINVAL;
	}

	imm = reg0->var_off.value;
	if (nfp_prog->type == BPF_PROG_TYPE_SCHED_CLS &&
	    imm <= TC_ACT_REDIRECT &&
	    imm != TC_ACT_SHOT && imm != TC_ACT_STOLEN &&
	    imm != TC_ACT_QUEUED) {
		pr_vlog(env, "unsupported exit state: %d, imm: %llx\n",
			reg0->type, imm);
		return -EINVAL;
	}

	return 0;
}