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

/* Variables and functions */
 int /*<<< orphan*/  MCP51_SMBUS_SETUP_B ; 
 int MCP51_SMBUS_SETUP_B_TCO_REBOOT ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  nv_tco_miscdev ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tco_pci ; 
 int /*<<< orphan*/  tco_timer_stop () ; 
 int /*<<< orphan*/  tcobase ; 

__attribute__((used)) static void nv_tco_cleanup(void)
{
	u32 val;

	/* Stop the timer before we leave */
	if (!nowayout)
		tco_timer_stop();

	/* Set the NO_REBOOT bit to prevent later reboots, just for sure */
	pci_read_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	val &= ~MCP51_SMBUS_SETUP_B_TCO_REBOOT;
	pci_write_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, val);
	pci_read_config_dword(tco_pci, MCP51_SMBUS_SETUP_B, &val);
	if (val & MCP51_SMBUS_SETUP_B_TCO_REBOOT) {
		pr_crit("Couldn't unset REBOOT bit.  Machine may soon reset\n");
	}

	/* Deregister */
	misc_deregister(&nv_tco_miscdev);
	release_region(tcobase, 0x10);
}