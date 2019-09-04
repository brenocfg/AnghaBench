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
 unsigned int WDISP19 (unsigned int) ; 
 unsigned int WDISP22 (unsigned int) ; 
 unsigned int XCC ; 
 int /*<<< orphan*/  emit (unsigned int,struct jit_ctx*) ; 

__attribute__((used)) static void emit_branch(unsigned int br_opc, unsigned int from_idx, unsigned int to_idx,
			struct jit_ctx *ctx)
{
	unsigned int off = to_idx - from_idx;

	if (br_opc & XCC)
		emit(br_opc | WDISP19(off << 2), ctx);
	else
		emit(br_opc | WDISP22(off << 2), ctx);
}