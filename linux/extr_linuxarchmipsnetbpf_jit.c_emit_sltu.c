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
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sltu ; 

__attribute__((used)) static inline void emit_sltu(unsigned int dst, unsigned int src1,
			     unsigned int src2, struct jit_ctx *ctx)
{
	emit_instr(ctx, sltu, dst, src1, src2);
}