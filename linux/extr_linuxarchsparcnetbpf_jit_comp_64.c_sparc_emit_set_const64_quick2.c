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
 int IMMED ; 
 int OR ; 
 int RD (unsigned int) ; 
 int RS1 (unsigned int) ; 
 int S13 (unsigned long) ; 
 int /*<<< orphan*/  SLLX ; 
 int /*<<< orphan*/  emit (int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_alu_K (int /*<<< orphan*/ ,unsigned int,int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_loadimm32 (unsigned long,unsigned int,struct jit_ctx*) ; 

__attribute__((used)) static void sparc_emit_set_const64_quick2(unsigned long high_bits,
					  unsigned long low_imm,
					  unsigned int dest,
					  int shift_count, struct jit_ctx *ctx)
{
	emit_loadimm32(high_bits, dest, ctx);

	/* Now shift it up into place.  */
	emit_alu_K(SLLX, dest, shift_count, ctx);

	/* If there is a low immediate part piece, finish up by
	 * putting that in as well.
	 */
	if (low_imm != 0)
		emit(OR | IMMED | RS1(dest) | S13(low_imm) | RD(dest), ctx);
}