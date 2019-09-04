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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  G0 ; 
 int IMMED ; 
 int OR ; 
 int RD (unsigned int) ; 
 int RS1 (int /*<<< orphan*/ ) ; 
 int S13 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit (int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_set_const_sext (int /*<<< orphan*/ ,unsigned int,struct jit_ctx*) ; 
 scalar_t__ is_simm13 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_loadimm_sext(s32 K, unsigned int dest, struct jit_ctx *ctx)
{
	if (is_simm13(K)) {
		/* or %g0, K, DEST */
		emit(OR | IMMED | RS1(G0) | S13(K) | RD(dest), ctx);
	} else {
		emit_set_const_sext(K, dest, ctx);
	}
}