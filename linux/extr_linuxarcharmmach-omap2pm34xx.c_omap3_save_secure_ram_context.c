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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ OMAP2_DEVICE_TYPE_GP ; 
 int /*<<< orphan*/  OMAP3_SAVE_SECURE_RAM_SZ ; 
 int PWRDM_POWER_ON ; 
 int /*<<< orphan*/  mpu_pwrdm ; 
 scalar_t__ omap3_save_secure_ram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3_secure_ram_storage ; 
 scalar_t__ omap_type () ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int pwrdm_read_next_pwrst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_next_pwrst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap3_save_secure_ram_context(void)
{
	u32 ret;
	int mpu_next_state = pwrdm_read_next_pwrst(mpu_pwrdm);

	if (omap_type() != OMAP2_DEVICE_TYPE_GP) {
		/*
		 * MPU next state must be set to POWER_ON temporarily,
		 * otherwise the WFI executed inside the ROM code
		 * will hang the system.
		 */
		pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_ON);
		ret = omap3_save_secure_ram(omap3_secure_ram_storage,
					    OMAP3_SAVE_SECURE_RAM_SZ);
		pwrdm_set_next_pwrst(mpu_pwrdm, mpu_next_state);
		/* Following is for error tracking, it should not happen */
		if (ret) {
			pr_err("save_secure_sram() returns %08x\n", ret);
			while (1)
				;
		}
	}
}