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
struct user_pt_regs {int pstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PSR_AA32_A_BIT ; 
 int PSR_AA32_C_BIT ; 
 int PSR_AA32_E_BIT ; 
 int PSR_AA32_F_BIT ; 
 int PSR_AA32_GE_MASK ; 
 int PSR_AA32_IT_MASK ; 
 int PSR_AA32_I_BIT ; 
 int PSR_AA32_N_BIT ; 
 int PSR_AA32_Q_BIT ; 
 int PSR_AA32_T_BIT ; 
 int PSR_AA32_V_BIT ; 
 int PSR_AA32_Z_BIT ; 
 int PSR_MODE32_BIT ; 
 int SPSR_EL1_AARCH32_RES0_BITS ; 
 int /*<<< orphan*/  system_supports_mixed_endian_el0 () ; 
 scalar_t__ user_mode (struct user_pt_regs*) ; 

__attribute__((used)) static int valid_compat_regs(struct user_pt_regs *regs)
{
	regs->pstate &= ~SPSR_EL1_AARCH32_RES0_BITS;

	if (!system_supports_mixed_endian_el0()) {
		if (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
			regs->pstate |= PSR_AA32_E_BIT;
		else
			regs->pstate &= ~PSR_AA32_E_BIT;
	}

	if (user_mode(regs) && (regs->pstate & PSR_MODE32_BIT) &&
	    (regs->pstate & PSR_AA32_A_BIT) == 0 &&
	    (regs->pstate & PSR_AA32_I_BIT) == 0 &&
	    (regs->pstate & PSR_AA32_F_BIT) == 0) {
		return 1;
	}

	/*
	 * Force PSR to a valid 32-bit EL0t, preserving the same bits as
	 * arch/arm.
	 */
	regs->pstate &= PSR_AA32_N_BIT | PSR_AA32_Z_BIT |
			PSR_AA32_C_BIT | PSR_AA32_V_BIT |
			PSR_AA32_Q_BIT | PSR_AA32_IT_MASK |
			PSR_AA32_GE_MASK | PSR_AA32_E_BIT |
			PSR_AA32_T_BIT;
	regs->pstate |= PSR_MODE32_BIT;

	return 0;
}