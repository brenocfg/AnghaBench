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
typedef  int /*<<< orphan*/  ptr ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_load_imm (int /*<<< orphan*/ ,scalar_t__,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  r_tmp ; 
 int /*<<< orphan*/  xori ; 

__attribute__((used)) static inline void emit_xori(ptr dst, ptr src, u32 imm, struct jit_ctx *ctx)
{
	/* If imm does not fit in u16 then load it to register */
	if (imm >= BIT(16)) {
		emit_load_imm(r_tmp, imm, ctx);
		emit_xor(dst, src, r_tmp, ctx);
	} else {
		emit_instr(ctx, xori, dst, src, imm);
	}
}