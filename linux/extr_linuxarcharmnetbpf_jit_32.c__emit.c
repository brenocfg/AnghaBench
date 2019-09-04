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
struct jit_ctx {int* target; size_t idx; } ;

/* Variables and functions */
 int __opcode_to_mem_arm (int) ; 

__attribute__((used)) static inline void _emit(int cond, u32 inst, struct jit_ctx *ctx)
{
	inst |= (cond << 28);
	inst = __opcode_to_mem_arm(inst);

	if (ctx->target != NULL)
		ctx->target[ctx->idx] = inst;

	ctx->idx++;
}