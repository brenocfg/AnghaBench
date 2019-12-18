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
struct TYPE_2__ {scalar_t__ hotkey_mask; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ TPACPI_LIFE_EXITING ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int const hotkey_acpi_mask ; 
 int /*<<< orphan*/  hotkey_mask_get () ; 
 int /*<<< orphan*/  hotkey_mask_warn_incomplete_mask () ; 
 int hotkey_source_mask ; 
 int /*<<< orphan*/  pr_notice (char*,int const,int const) ; 
 TYPE_1__ tp_features ; 
 scalar_t__ tpacpi_lifecycle ; 

__attribute__((used)) static int hotkey_mask_set(u32 mask)
{
	int i;
	int rc = 0;

	const u32 fwmask = mask & ~hotkey_source_mask;

	if (tp_features.hotkey_mask) {
		for (i = 0; i < 32; i++) {
			if (!acpi_evalf(hkey_handle,
					NULL, "MHKM", "vdd", i + 1,
					!!(mask & (1 << i)))) {
				rc = -EIO;
				break;
			}
		}
	}

	/*
	 * We *must* make an inconditional call to hotkey_mask_get to
	 * refresh hotkey_acpi_mask and update hotkey_user_mask
	 *
	 * Take the opportunity to also log when we cannot _enable_
	 * a given event.
	 */
	if (!hotkey_mask_get() && !rc && (fwmask & ~hotkey_acpi_mask)) {
		pr_notice("asked for hotkey mask 0x%08x, but firmware forced it to 0x%08x\n",
			  fwmask, hotkey_acpi_mask);
	}

	if (tpacpi_lifecycle != TPACPI_LIFE_EXITING)
		hotkey_mask_warn_incomplete_mask();

	return rc;
}