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
struct tb_nhi {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VS_CAP_22 ; 
 int VS_CAP_22_DMA_DELAY_MASK ; 
 int VS_CAP_22_DMA_DELAY_SHIFT ; 
 int VS_CAP_22_FORCE_POWER ; 
 int /*<<< orphan*/  VS_CAP_9 ; 
 int VS_CAP_9_FW_READY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int icl_nhi_force_power(struct tb_nhi *nhi, bool power)
{
	u32 vs_cap;

	/*
	 * The Thunderbolt host controller is present always in Ice Lake
	 * but the firmware may not be loaded and running (depending
	 * whether there is device connected and so on). Each time the
	 * controller is used we need to "Force Power" it first and wait
	 * for the firmware to indicate it is up and running. This "Force
	 * Power" is really not about actually powering on/off the
	 * controller so it is accessible even if "Force Power" is off.
	 *
	 * The actual power management happens inside shared ACPI power
	 * resources using standard ACPI methods.
	 */
	pci_read_config_dword(nhi->pdev, VS_CAP_22, &vs_cap);
	if (power) {
		vs_cap &= ~VS_CAP_22_DMA_DELAY_MASK;
		vs_cap |= 0x22 << VS_CAP_22_DMA_DELAY_SHIFT;
		vs_cap |= VS_CAP_22_FORCE_POWER;
	} else {
		vs_cap &= ~VS_CAP_22_FORCE_POWER;
	}
	pci_write_config_dword(nhi->pdev, VS_CAP_22, vs_cap);

	if (power) {
		unsigned int retries = 10;
		u32 val;

		/* Wait until the firmware tells it is up and running */
		do {
			pci_read_config_dword(nhi->pdev, VS_CAP_9, &val);
			if (val & VS_CAP_9_FW_READY)
				return 0;
			msleep(250);
		} while (--retries);

		return -ETIMEDOUT;
	}

	return 0;
}