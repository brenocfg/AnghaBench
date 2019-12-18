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
 int /*<<< orphan*/  TPACPI_DBG_RFKILL ; 
 int /*<<< orphan*/  TP_ACPI_WGSV_SAVE_STATE ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wan_shutdown(void)
{
	/* Order firmware to save current state to NVRAM */
	if (!acpi_evalf(NULL, NULL, "\\WGSV", "vd",
			TP_ACPI_WGSV_SAVE_STATE))
		pr_notice("failed to save WWAN state to NVRAM\n");
	else
		vdbg_printk(TPACPI_DBG_RFKILL,
			"WWAN state saved to NVRAM\n");
}