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
struct jit_ctx {int /*<<< orphan*/  idx; int /*<<< orphan*/  epilogue_offset; } ;

/* Variables and functions */
 size_t BPF_REG_0 ; 
 int /*<<< orphan*/  G0 ; 
 int /*<<< orphan*/  I7 ; 
 int IMMED ; 
 int JMPL ; 
 int /*<<< orphan*/  O0 ; 
 int RD (int /*<<< orphan*/ ) ; 
 int RESTORE ; 
 int RS1 (int /*<<< orphan*/ ) ; 
 int RS2 (int /*<<< orphan*/ ) ; 
 int S13 (int) ; 
 int /*<<< orphan*/ * bpf2sparc ; 
 int /*<<< orphan*/  emit (int,struct jit_ctx*) ; 

__attribute__((used)) static void build_epilogue(struct jit_ctx *ctx)
{
	ctx->epilogue_offset = ctx->idx;

	/* ret (jmpl %i7 + 8, %g0) */
	emit(JMPL | IMMED | RS1(I7) | S13(8) | RD(G0), ctx);

	/* restore %i5, %g0, %o0 */
	emit(RESTORE | RS1(bpf2sparc[BPF_REG_0]) | RS2(G0) | RD(O0), ctx);
}