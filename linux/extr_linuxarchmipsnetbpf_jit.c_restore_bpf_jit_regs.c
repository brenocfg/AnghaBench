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
typedef  int u32 ;
struct jit_ctx {int flags; } ;

/* Variables and functions */
 scalar_t__ MIPS_R_S0 ; 
 int SEEN_CALL ; 
 int SEEN_SREG_SFT ; 
 scalar_t__ SZREG ; 
 int /*<<< orphan*/  align_sp (unsigned int) ; 
 int /*<<< orphan*/  emit_load_stack_reg (scalar_t__,int /*<<< orphan*/ ,int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_stack_offset (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ r_ra ; 
 int /*<<< orphan*/  r_sp ; 

__attribute__((used)) static void restore_bpf_jit_regs(struct jit_ctx *ctx,
				 unsigned int offset)
{
	int i, real_off = 0;
	u32 sflags, tmp_flags;

	tmp_flags = sflags = ctx->flags >> SEEN_SREG_SFT;
	/* sflags is a bitmap */
	i = 0;
	while (tmp_flags) {
		if ((sflags >> i) & 0x1) {
			emit_load_stack_reg(MIPS_R_S0 + i, r_sp, real_off,
					    ctx);
			real_off += SZREG;
		}
		i++;
		tmp_flags >>= 1;
	}

	/* restore return address */
	if (ctx->flags & SEEN_CALL)
		emit_load_stack_reg(r_ra, r_sp, real_off, ctx);

	/* Restore the sp and discard the scrach memory */
	if (offset)
		emit_stack_offset(align_sp(offset), ctx);
}