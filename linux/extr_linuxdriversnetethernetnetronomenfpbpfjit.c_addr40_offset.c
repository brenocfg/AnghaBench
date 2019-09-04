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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ swreg ;
struct nfp_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_ADD_C ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ imm_a (struct nfp_prog*) ; 
 scalar_t__ imm_b (struct nfp_prog*) ; 
 scalar_t__ reg_a (scalar_t__) ; 
 scalar_t__ reg_b (scalar_t__) ; 
 scalar_t__ reg_imm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
addr40_offset(struct nfp_prog *nfp_prog, u8 src_gpr, swreg offset,
	      swreg *rega, swreg *regb)
{
	if (offset == reg_imm(0)) {
		*rega = reg_a(src_gpr);
		*regb = reg_b(src_gpr + 1);
		return;
	}

	emit_alu(nfp_prog, imm_a(nfp_prog), reg_a(src_gpr), ALU_OP_ADD, offset);
	emit_alu(nfp_prog, imm_b(nfp_prog), reg_b(src_gpr + 1), ALU_OP_ADD_C,
		 reg_imm(0));
	*rega = imm_a(nfp_prog);
	*regb = imm_b(nfp_prog);
}