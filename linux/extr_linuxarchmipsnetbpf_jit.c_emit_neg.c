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
 int /*<<< orphan*/  emit_subu (unsigned int,int /*<<< orphan*/ ,unsigned int,struct jit_ctx*) ; 
 int /*<<< orphan*/  r_zero ; 

__attribute__((used)) static inline void emit_neg(unsigned int reg, struct jit_ctx *ctx)
{
	emit_subu(reg, r_zero, reg, ctx);
}