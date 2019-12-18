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
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;
struct jmp_code_map {int /*<<< orphan*/  br_mask; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct jmp_code_map const*) ; 
 int BPF_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 struct jmp_code_map const* jmp_code_map ; 

__attribute__((used)) static const struct jmp_code_map *nfp_jmp_code_get(struct nfp_insn_meta *meta)
{
	unsigned int op;

	op = BPF_OP(meta->insn.code) >> 4;
	/* br_mask of 0 is BR_BEQ which we don't use in jump code table */
	if (WARN_ONCE(op >= ARRAY_SIZE(jmp_code_map) ||
		      !jmp_code_map[op].br_mask,
		      "no code found for jump instruction"))
		return NULL;

	return &jmp_code_map[op];
}