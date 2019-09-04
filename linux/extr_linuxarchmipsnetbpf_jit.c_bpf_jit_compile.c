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
struct jit_ctx {unsigned int idx; unsigned int prologue_bytes; int /*<<< orphan*/ * offsets; struct jit_ctx* target; struct bpf_prog* skf; } ;
struct bpf_prog {int jited; void* bpf_func; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  ptr ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bpf_jit_dump (scalar_t__,unsigned int,int,struct jit_ctx*) ; 
 int bpf_jit_enable ; 
 scalar_t__ build_body (struct jit_ctx*) ; 
 int /*<<< orphan*/  build_epilogue (struct jit_ctx*) ; 
 int /*<<< orphan*/  build_prologue (struct jit_ctx*) ; 
 int /*<<< orphan*/  flush_icache_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct jit_ctx*,int /*<<< orphan*/ ,unsigned int) ; 
 struct jit_ctx* module_alloc (unsigned int) ; 

void bpf_jit_compile(struct bpf_prog *fp)
{
	struct jit_ctx ctx;
	unsigned int alloc_size, tmp_idx;

	if (!bpf_jit_enable)
		return;

	memset(&ctx, 0, sizeof(ctx));

	ctx.offsets = kcalloc(fp->len + 1, sizeof(*ctx.offsets), GFP_KERNEL);
	if (ctx.offsets == NULL)
		return;

	ctx.skf = fp;

	if (build_body(&ctx))
		goto out;

	tmp_idx = ctx.idx;
	build_prologue(&ctx);
	ctx.prologue_bytes = (ctx.idx - tmp_idx) * 4;
	/* just to complete the ctx.idx count */
	build_epilogue(&ctx);

	alloc_size = 4 * ctx.idx;
	ctx.target = module_alloc(alloc_size);
	if (ctx.target == NULL)
		goto out;

	/* Clean it */
	memset(ctx.target, 0, alloc_size);

	ctx.idx = 0;

	/* Generate the actual JIT code */
	build_prologue(&ctx);
	build_body(&ctx);
	build_epilogue(&ctx);

	/* Update the icache */
	flush_icache_range((ptr)ctx.target, (ptr)(ctx.target + ctx.idx));

	if (bpf_jit_enable > 1)
		/* Dump JIT code */
		bpf_jit_dump(fp->len, alloc_size, 2, ctx.target);

	fp->bpf_func = (void *)ctx.target;
	fp->jited = 1;

out:
	kfree(ctx.offsets);
}