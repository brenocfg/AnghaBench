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
typedef  int u32 ;
struct nfp_prog {int /*<<< orphan*/ * prog; } ;
struct nfp_insn_meta {int /*<<< orphan*/  off; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ immed_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  immed_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
nfp_fixup_immed_relo(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
		     struct nfp_insn_meta *jmp_dst, u32 br_idx)
{
	if (immed_get_value(nfp_prog->prog[br_idx + 1])) {
		pr_err("BUG: failed to fix up callee register saving\n");
		return -EINVAL;
	}

	immed_set_value(&nfp_prog->prog[br_idx + 1], jmp_dst->off);

	return 0;
}