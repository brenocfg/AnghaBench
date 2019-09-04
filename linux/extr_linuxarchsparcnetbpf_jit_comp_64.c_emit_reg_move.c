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
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G0 ; 
 int OR ; 
 int RD (int /*<<< orphan*/ ) ; 
 int RS1 (int /*<<< orphan*/ ) ; 
 int RS2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit (int,struct jit_ctx*) ; 

__attribute__((used)) static void emit_reg_move(u32 from, u32 to, struct jit_ctx *ctx)
{
	emit(OR | RS1(G0) | RS2(from) | RD(to), ctx);
}