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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct jit_ctx {unsigned int imm_count; scalar_t__* imms; int* offsets; int idx; int /*<<< orphan*/  flags; scalar_t__* target; scalar_t__ epilogue_bytes; scalar_t__ prologue_bytes; TYPE_1__* prog; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IMM_OVERFLOW ; 

__attribute__((used)) static u16 imm_offset(u32 k, struct jit_ctx *ctx)
{
	unsigned int i = 0, offset;
	u16 imm;

	/* on the "fake" run we just count them (duplicates included) */
	if (ctx->target == NULL) {
		ctx->imm_count++;
		return 0;
	}

	while ((i < ctx->imm_count) && ctx->imms[i]) {
		if (ctx->imms[i] == k)
			break;
		i++;
	}

	if (ctx->imms[i] == 0)
		ctx->imms[i] = k;

	/* constants go just after the epilogue */
	offset =  ctx->offsets[ctx->prog->len - 1] * 4;
	offset += ctx->prologue_bytes;
	offset += ctx->epilogue_bytes;
	offset += i * 4;

	ctx->target[offset / 4] = k;

	/* PC in ARM mode == address of the instruction + 8 */
	imm = offset - (8 + ctx->idx * 4);

	if (imm & ~0xfff) {
		/*
		 * literal pool is too far, signal it into flags. we
		 * can only detect it on the second pass unfortunately.
		 */
		ctx->flags |= FLAG_IMM_OVERFLOW;
		return 0;
	}

	return imm;
}