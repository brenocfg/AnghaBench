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
struct jit_ctx {int flags; } ;

/* Variables and functions */
 int BPF_MEMWORDS ; 
 int SEEN_CALL ; 
 int SEEN_MEM ; 
 int SEEN_SREG_SFT ; 
 int SZREG ; 
 int hweight32 (int) ; 

__attribute__((used)) static unsigned int get_stack_depth(struct jit_ctx *ctx)
{
	int sp_off = 0;


	/* How may s* regs do we need to preserved? */
	sp_off += hweight32(ctx->flags >> SEEN_SREG_SFT) * SZREG;

	if (ctx->flags & SEEN_MEM)
		sp_off += 4 * BPF_MEMWORDS; /* BPF_MEMWORDS are 32-bit */

	if (ctx->flags & SEEN_CALL)
		sp_off += SZREG; /* Space for our ra register */

	return sp_off;
}