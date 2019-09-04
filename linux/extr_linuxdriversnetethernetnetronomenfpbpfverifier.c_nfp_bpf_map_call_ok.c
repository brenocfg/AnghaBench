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
typedef  int /*<<< orphan*/  u32 ;
struct nfp_insn_meta {int dummy; } ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,char const*) ; 

__attribute__((used)) static bool
nfp_bpf_map_call_ok(const char *fname, struct bpf_verifier_env *env,
		    struct nfp_insn_meta *meta,
		    u32 helper_tgt, const struct bpf_reg_state *reg1)
{
	if (!helper_tgt) {
		pr_vlog(env, "%s: not supported by FW\n", fname);
		return false;
	}

	return true;
}