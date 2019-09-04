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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_SIZE ; 
 unsigned int ESR_ELx_SYS64_ISS_RT_MASK ; 
 unsigned int ESR_ELx_SYS64_ISS_RT_SHIFT ; 
 int /*<<< orphan*/  arch_counter_get_cntvct () ; 
 int /*<<< orphan*/  arm64_skip_faulting_instruction (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_regs_write_reg (struct pt_regs*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cntvct_read_handler(unsigned int esr, struct pt_regs *regs)
{
	int rt = (esr & ESR_ELx_SYS64_ISS_RT_MASK) >> ESR_ELx_SYS64_ISS_RT_SHIFT;

	pt_regs_write_reg(regs, rt, arch_counter_get_cntvct());
	arm64_skip_faulting_instruction(regs, AARCH64_INSN_SIZE);
}