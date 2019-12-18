#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfp_prog {struct nfp_insn_meta* verifier_meta; } ;
struct TYPE_8__ {int code; scalar_t__ src_reg; scalar_t__ dst_reg; } ;
struct nfp_insn_meta {TYPE_4__ insn; } ;
struct bpf_verifier_env {TYPE_3__* prog; } ;
struct TYPE_7__ {TYPE_2__* aux; } ;
struct TYPE_6__ {TYPE_1__* offload; } ;
struct TYPE_5__ {struct nfp_prog* dev_priv; } ;

/* Variables and functions */
 int BPF_EXIT ; 
 int BPF_JMP ; 
 int EINVAL ; 
 scalar_t__ MAX_BPF_REG ; 
 scalar_t__ is_mbpf_alu (struct nfp_insn_meta*) ; 
 scalar_t__ is_mbpf_helper_call (struct nfp_insn_meta*) ; 
 scalar_t__ is_mbpf_load (struct nfp_insn_meta*) ; 
 scalar_t__ is_mbpf_store (struct nfp_insn_meta*) ; 
 scalar_t__ is_mbpf_xadd (struct nfp_insn_meta*) ; 
 int nfp_bpf_check_alu (struct nfp_prog*,struct nfp_insn_meta*,struct bpf_verifier_env*) ; 
 int nfp_bpf_check_exit (struct nfp_prog*,struct bpf_verifier_env*) ; 
 int nfp_bpf_check_helper_call (struct nfp_prog*,struct bpf_verifier_env*,struct nfp_insn_meta*) ; 
 int nfp_bpf_check_ptr (struct nfp_prog*,struct nfp_insn_meta*,struct bpf_verifier_env*,scalar_t__) ; 
 int nfp_bpf_check_store (struct nfp_prog*,struct nfp_insn_meta*,struct bpf_verifier_env*) ; 
 int nfp_bpf_check_xadd (struct nfp_prog*,struct nfp_insn_meta*,struct bpf_verifier_env*) ; 
 struct nfp_insn_meta* nfp_bpf_goto_meta (struct nfp_prog*,struct nfp_insn_meta*,int) ; 
 int /*<<< orphan*/  nfp_bpf_supported_opcode (int) ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,...) ; 

int nfp_verify_insn(struct bpf_verifier_env *env, int insn_idx,
		    int prev_insn_idx)
{
	struct nfp_prog *nfp_prog = env->prog->aux->offload->dev_priv;
	struct nfp_insn_meta *meta = nfp_prog->verifier_meta;

	meta = nfp_bpf_goto_meta(nfp_prog, meta, insn_idx);
	nfp_prog->verifier_meta = meta;

	if (!nfp_bpf_supported_opcode(meta->insn.code)) {
		pr_vlog(env, "instruction %#02x not supported\n",
			meta->insn.code);
		return -EINVAL;
	}

	if (meta->insn.src_reg >= MAX_BPF_REG ||
	    meta->insn.dst_reg >= MAX_BPF_REG) {
		pr_vlog(env, "program uses extended registers - jit hardening?\n");
		return -EINVAL;
	}

	if (is_mbpf_helper_call(meta))
		return nfp_bpf_check_helper_call(nfp_prog, env, meta);
	if (meta->insn.code == (BPF_JMP | BPF_EXIT))
		return nfp_bpf_check_exit(nfp_prog, env);

	if (is_mbpf_load(meta))
		return nfp_bpf_check_ptr(nfp_prog, meta, env,
					 meta->insn.src_reg);
	if (is_mbpf_store(meta))
		return nfp_bpf_check_store(nfp_prog, meta, env);

	if (is_mbpf_xadd(meta))
		return nfp_bpf_check_xadd(nfp_prog, meta, env);

	if (is_mbpf_alu(meta))
		return nfp_bpf_check_alu(nfp_prog, meta, env);

	return 0;
}