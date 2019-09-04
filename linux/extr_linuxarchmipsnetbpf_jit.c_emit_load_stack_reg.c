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
typedef  int /*<<< orphan*/  ptr ;

/* Variables and functions */
 int /*<<< orphan*/  LW ; 
 int /*<<< orphan*/  emit_long_instr (struct jit_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void emit_load_stack_reg(ptr reg, ptr base,
				       unsigned int offset,
				       struct jit_ctx *ctx)
{
	emit_long_instr(ctx, LW, reg, offset, base);
}