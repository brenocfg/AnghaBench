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
 int /*<<< orphan*/  MIPS_COND_ALL ; 
 int /*<<< orphan*/  emit_bcond (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct jit_ctx*) ; 
 int /*<<< orphan*/  r_zero ; 

__attribute__((used)) static inline void emit_b(unsigned int imm, struct jit_ctx *ctx)
{
	emit_bcond(MIPS_COND_ALL, r_zero, r_zero, imm, ctx);
}