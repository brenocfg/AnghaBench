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
struct jit_ctx {int* offsets; int idx; int /*<<< orphan*/  gen_b_offsets; } ;

/* Variables and functions */
 int OFFSETS_B_CONV ; 

__attribute__((used)) static u32 b_imm(unsigned int tgt, struct jit_ctx *ctx)
{
	if (!ctx->gen_b_offsets)
		return 0;

	/*
	 * We want a pc-relative branch.  tgt is the instruction offset
	 * we want to jump to.

	 * Branch on MIPS:
	 * I: target_offset <- sign_extend(offset)
	 * I+1: PC += target_offset (delay slot)
	 *
	 * ctx->idx currently points to the branch instruction
	 * but the offset is added to the delay slot so we need
	 * to subtract 4.
	 */
	return (ctx->offsets[tgt] & ~OFFSETS_B_CONV) -
		(ctx->idx * 4) - 4;
}