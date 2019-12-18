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
 int BIT (int) ; 
 int /*<<< orphan*/  TPACPI_DBG_INIT ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool kbdlight_is_supported(void)
{
	int status = 0;

	if (!hkey_handle)
		return false;

	if (!acpi_has_method(hkey_handle, "MLCG")) {
		vdbg_printk(TPACPI_DBG_INIT, "kbdlight MLCG is unavailable\n");
		return false;
	}

	if (!acpi_evalf(hkey_handle, &status, "MLCG", "qdd", 0)) {
		vdbg_printk(TPACPI_DBG_INIT, "kbdlight MLCG failed\n");
		return false;
	}

	if (status < 0) {
		vdbg_printk(TPACPI_DBG_INIT, "kbdlight MLCG err: %d\n", status);
		return false;
	}

	vdbg_printk(TPACPI_DBG_INIT, "kbdlight MLCG returned 0x%x\n", status);
	/*
	 * Guessed test for keyboard backlight:
	 *
	 * Machines with backlight keyboard return:
	 *   b010100000010000000XX - ThinkPad X1 Carbon 3rd
	 *   b110100010010000000XX - ThinkPad x230
	 *   b010100000010000000XX - ThinkPad x240
	 *   b010100000010000000XX - ThinkPad W541
	 * (XX is current backlight level)
	 *
	 * Machines without backlight keyboard return:
	 *   b10100001000000000000 - ThinkPad x230
	 *   b10110001000000000000 - ThinkPad E430
	 *   b00000000000000000000 - ThinkPad E450
	 *
	 * Candidate BITs for detection test (XOR):
	 *   b01000000001000000000
	 *              ^
	 */
	return status & BIT(9);
}