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
 int /*<<< orphan*/  emit_addu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  r_zero ; 

__attribute__((used)) static inline void emit_jit_reg_move(ptr dst, ptr src, struct jit_ctx *ctx)
{
	emit_addu(dst, src, r_zero, ctx);
}