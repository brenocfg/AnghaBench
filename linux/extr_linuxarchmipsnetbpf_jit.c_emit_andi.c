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
typedef  scalar_t__ u32 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  andi ; 
 int /*<<< orphan*/  emit_and (unsigned int,unsigned int,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,unsigned int,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  emit_load_imm (int /*<<< orphan*/ ,scalar_t__,struct jit_ctx*) ; 
 int /*<<< orphan*/  r_tmp ; 

__attribute__((used)) static inline void emit_andi(unsigned int dst, unsigned int src,
			     u32 imm, struct jit_ctx *ctx)
{
	/* If imm does not fit in u16 then load it to register */
	if (imm >= BIT(16)) {
		emit_load_imm(r_tmp, imm, ctx);
		emit_and(dst, src, r_tmp, ctx);
	} else {
		emit_instr(ctx, andi, dst, src, imm);
	}
}