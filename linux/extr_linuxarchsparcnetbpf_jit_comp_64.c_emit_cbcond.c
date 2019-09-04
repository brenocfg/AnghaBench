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
typedef  int /*<<< orphan*/  u8 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 unsigned int RS1 (int /*<<< orphan*/  const) ; 
 unsigned int RS2 (int /*<<< orphan*/  const) ; 
 unsigned int WDISP10 (unsigned int) ; 
 int /*<<< orphan*/  emit (unsigned int,struct jit_ctx*) ; 

__attribute__((used)) static void emit_cbcond(unsigned int cb_opc, unsigned int from_idx, unsigned int to_idx,
			const u8 dst, const u8 src, struct jit_ctx *ctx)
{
	unsigned int off = to_idx - from_idx;

	emit(cb_opc | WDISP10(off << 2) | RS1(dst) | RS2(src), ctx);
}