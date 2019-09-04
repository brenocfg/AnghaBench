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
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {size_t idx; int /*<<< orphan*/ * target; } ;

/* Variables and functions */
 int /*<<< orphan*/  uasm_i_divu (int /*<<< orphan*/ **,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mfhi (int /*<<< orphan*/ **,unsigned int) ; 

__attribute__((used)) static inline void emit_mod(unsigned int dst, unsigned int src,
			    struct jit_ctx *ctx)
{
	if (ctx->target != NULL) {
		u32 *p = &ctx->target[ctx->idx];
		uasm_i_divu(&p, dst, src);
		p = &ctx->target[ctx->idx + 1];
		uasm_i_mfhi(&p, dst);
	}
	ctx->idx += 2; /* 2 insts */
}