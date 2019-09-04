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
struct jit_ctx {int* reg_val_types; int* offsets; int idx; int /*<<< orphan*/ * target; struct bpf_prog* skf; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; } ;
struct bpf_insn {int code; } ;

/* Variables and functions */
 int BPF_EXIT ; 
 int BPF_JMP ; 
 int OFFSETS_B_CONV ; 
 int RVT_VISITED_MASK ; 
 int build_one_insn (struct bpf_insn const*,struct jit_ctx*,int,int) ; 

__attribute__((used)) static int build_int_body(struct jit_ctx *ctx)
{
	const struct bpf_prog *prog = ctx->skf;
	const struct bpf_insn *insn;
	int i, r;

	for (i = 0; i < prog->len; ) {
		insn = prog->insnsi + i;
		if ((ctx->reg_val_types[i] & RVT_VISITED_MASK) == 0) {
			/* dead instruction, don't emit it. */
			i++;
			continue;
		}

		if (ctx->target == NULL)
			ctx->offsets[i] = (ctx->offsets[i] & OFFSETS_B_CONV) | (ctx->idx * 4);

		r = build_one_insn(insn, ctx, i, prog->len);
		if (r < 0)
			return r;
		i += r;
	}
	/* epilogue offset */
	if (ctx->target == NULL)
		ctx->offsets[i] = ctx->idx * 4;

	/*
	 * All exits have an offset of the epilogue, some offsets may
	 * not have been set due to banch-around threading, so set
	 * them now.
	 */
	if (ctx->target == NULL)
		for (i = 0; i < prog->len; i++) {
			insn = prog->insnsi + i;
			if (insn->code == (BPF_JMP | BPF_EXIT))
				ctx->offsets[i] = ctx->idx * 4;
		}
	return 0;
}