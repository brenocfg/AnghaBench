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
 int TPACPI_HKEY_NVRAM_KNOWN_MASK ; 
 int hotkey_acpi_mask ; 
 int hotkey_all_mask ; 
 int hotkey_driver_mask ; 
 int hotkey_source_mask ; 
 int /*<<< orphan*/  pr_notice (char*,int const) ; 

__attribute__((used)) static void hotkey_mask_warn_incomplete_mask(void)
{
	/* log only what the user can fix... */
	const u32 wantedmask = hotkey_driver_mask &
		~(hotkey_acpi_mask | hotkey_source_mask) &
		(hotkey_all_mask | TPACPI_HKEY_NVRAM_KNOWN_MASK);

	if (wantedmask)
		pr_notice("required events 0x%08x not enabled!\n", wantedmask);
}