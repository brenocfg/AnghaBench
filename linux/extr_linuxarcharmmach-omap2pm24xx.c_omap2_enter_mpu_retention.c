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

/* Variables and functions */
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  OMAP24XX_PM_WKST2 ; 
 int /*<<< orphan*/  PM_WKST ; 
 int /*<<< orphan*/  PM_WKST1 ; 
 int /*<<< orphan*/  PWRDM_POWER_ON ; 
 int /*<<< orphan*/  PWRDM_POWER_RET ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int /*<<< orphan*/  mpu_pwrdm ; 
 scalar_t__ omap2_allow_mpu_retention () ; 
 int /*<<< orphan*/  omap_prm_clear_mod_irqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_next_pwrst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_enter_mpu_retention(void)
{
	const int zero = 0;

	/* The peripherals seem not to be able to wake up the MPU when
	 * it is in retention mode. */
	if (omap2_allow_mpu_retention()) {
		/* REVISIT: These write to reserved bits? */
		omap_prm_clear_mod_irqs(CORE_MOD, PM_WKST1, ~0);
		omap_prm_clear_mod_irqs(CORE_MOD, OMAP24XX_PM_WKST2, ~0);
		omap_prm_clear_mod_irqs(WKUP_MOD, PM_WKST, ~0);

		/* Try to enter MPU retention */
		pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_RET);

	} else {
		/* Block MPU retention */
		pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
	}

	/* WFI */
	asm("mcr p15, 0, %0, c7, c0, 4" : : "r" (zero) : "memory", "cc");

	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
}