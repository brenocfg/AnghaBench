#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int hotkey_mask_ff; } ;

/* Variables and functions */
 int const hotkey_acpi_mask ; 
 int const hotkey_driver_mask ; 
 int hotkey_mask_set (int const) ; 
 int const hotkey_source_mask ; 
 int hotkey_user_mask ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 TYPE_1__ tp_warned ; 

__attribute__((used)) static int hotkey_user_mask_set(const u32 mask)
{
	int rc;

	/* Give people a chance to notice they are doing something that
	 * is bound to go boom on their users sooner or later */
	if (!tp_warned.hotkey_mask_ff &&
	    (mask == 0xffff || mask == 0xffffff ||
	     mask == 0xffffffff)) {
		tp_warned.hotkey_mask_ff = 1;
		pr_notice("setting the hotkey mask to 0x%08x is likely not the best way to go about it\n",
			  mask);
		pr_notice("please consider using the driver defaults, and refer to up-to-date thinkpad-acpi documentation\n");
	}

	/* Try to enable what the user asked for, plus whatever we need.
	 * this syncs everything but won't enable bits in hotkey_user_mask */
	rc = hotkey_mask_set((mask | hotkey_driver_mask) & ~hotkey_source_mask);

	/* Enable the available bits in hotkey_user_mask */
	hotkey_user_mask = mask & (hotkey_acpi_mask | hotkey_source_mask);

	return rc;
}