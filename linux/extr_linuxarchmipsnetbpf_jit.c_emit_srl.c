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
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  emit_jit_reg_move (unsigned int,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  r_zero ; 
 int /*<<< orphan*/  srl ; 

__attribute__((used)) static inline void emit_srl(unsigned int dst, unsigned int src,
			    unsigned int sa, struct jit_ctx *ctx)
{
	/* sa is 5-bits long */
	if (sa >= BIT(5))
		/* Shifting >= 32 results in zero */
		emit_jit_reg_move(dst, r_zero, ctx);
	else
		emit_instr(ctx, srl, dst, src, sa);
}