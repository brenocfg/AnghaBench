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
 int PSR_A_BIT ; 
 int PSR_C_BIT ; 
 int PSR_D_BIT ; 
 int PSR_F_BIT ; 
 int PSR_I_BIT ; 
 int PSR_MODE32_BIT ; 
 int PSR_N_BIT ; 
 int PSR_V_BIT ; 
 int PSR_Z_BIT ; 
 int SPSR_EL1_AARCH64_RES0_BITS ; 
 scalar_t__ user_mode (struct user_pt_regs*) ; 

__attribute__((used)) static int valid_native_regs(struct user_pt_regs *regs)
{
	regs->pstate &= ~SPSR_EL1_AARCH64_RES0_BITS;

	if (user_mode(regs) && !(regs->pstate & PSR_MODE32_BIT) &&
	    (regs->pstate & PSR_D_BIT) == 0 &&
	    (regs->pstate & PSR_A_BIT) == 0 &&
	    (regs->pstate & PSR_I_BIT) == 0 &&
	    (regs->pstate & PSR_F_BIT) == 0) {
		return 1;
	}

	/* Force PSR to a valid 64-bit EL0t */
	regs->pstate &= PSR_N_BIT | PSR_Z_BIT | PSR_C_BIT | PSR_V_BIT;

	return 0;
}