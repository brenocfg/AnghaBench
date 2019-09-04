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
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit_jr (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_nop (struct jit_ctx*) ; 
 unsigned int get_stack_depth (struct jit_ctx*) ; 
 int /*<<< orphan*/  r_ra ; 
 int /*<<< orphan*/  restore_bpf_jit_regs (struct jit_ctx*,unsigned int) ; 

__attribute__((used)) static void build_epilogue(struct jit_ctx *ctx)
{
	unsigned int sp_off;

	/* Calculate the total offset for the stack pointer */

	sp_off = get_stack_depth(ctx);
	restore_bpf_jit_regs(ctx, sp_off);

	/* Return */
	emit_jr(r_ra, ctx);
	emit_nop(ctx);
}