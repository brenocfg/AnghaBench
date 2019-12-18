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
struct ath5k_ini {scalar_t__ ini_register; int ini_mode; int /*<<< orphan*/  ini_value; } ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
#define  AR5K_INI_READ 129 
#define  AR5K_INI_WRITE 128 
 scalar_t__ AR5K_PCU_MAX ; 
 scalar_t__ AR5K_PCU_MIN ; 
 int /*<<< orphan*/  AR5K_REG_WAIT (unsigned int) ; 
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ath5k_hw_ini_registers(struct ath5k_hw *ah, unsigned int size,
		const struct ath5k_ini *ini_regs, bool skip_pcu)
{
	unsigned int i;

	/* Write initial registers */
	for (i = 0; i < size; i++) {
		/* Skip PCU registers if
		 * requested */
		if (skip_pcu &&
				ini_regs[i].ini_register >= AR5K_PCU_MIN &&
				ini_regs[i].ini_register <= AR5K_PCU_MAX)
			continue;

		switch (ini_regs[i].ini_mode) {
		case AR5K_INI_READ:
			/* Cleared on read */
			ath5k_hw_reg_read(ah, ini_regs[i].ini_register);
			break;
		case AR5K_INI_WRITE:
		default:
			AR5K_REG_WAIT(i);
			ath5k_hw_reg_write(ah, ini_regs[i].ini_value,
					ini_regs[i].ini_register);
		}
	}
}