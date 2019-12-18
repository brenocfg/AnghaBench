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
struct TYPE_2__ {scalar_t__ has_adaptive_kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_ACPI_WAKEUP_NONE ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adaptive_keyboard_prev_mode ; 
 int /*<<< orphan*/  hkey_handle ; 
 scalar_t__ hotkey_autosleep_ack ; 
 int /*<<< orphan*/  hotkey_wakeup_reason ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static void hotkey_suspend(void)
{
	/* Do these on suspend, we get the events on early resume! */
	hotkey_wakeup_reason = TP_ACPI_WAKEUP_NONE;
	hotkey_autosleep_ack = 0;

	/* save previous mode of adaptive keyboard of X1 Carbon */
	if (tp_features.has_adaptive_kbd) {
		if (!acpi_evalf(hkey_handle, &adaptive_keyboard_prev_mode,
					"GTRW", "dd", 0)) {
			pr_err("Cannot read adaptive keyboard mode.\n");
		}
	}
}