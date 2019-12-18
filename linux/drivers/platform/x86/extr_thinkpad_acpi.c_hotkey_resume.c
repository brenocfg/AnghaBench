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
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adaptive_keyboard_prev_mode ; 
 int /*<<< orphan*/  hkey_handle ; 
 int /*<<< orphan*/  hotkey_acpi_mask ; 
 scalar_t__ hotkey_mask_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hotkey_poll_setup_safe (int) ; 
 scalar_t__ hotkey_status_set (int) ; 
 int /*<<< orphan*/  hotkey_tablet_mode_notify_change () ; 
 int /*<<< orphan*/  hotkey_wakeup_hotunplug_complete_notify_change () ; 
 int /*<<< orphan*/  hotkey_wakeup_reason_notify_change () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ tp_features ; 
 int /*<<< orphan*/  tpacpi_disable_brightness_delay () ; 
 int /*<<< orphan*/  tpacpi_send_radiosw_update () ; 

__attribute__((used)) static void hotkey_resume(void)
{
	tpacpi_disable_brightness_delay();

	if (hotkey_status_set(true) < 0 ||
	    hotkey_mask_set(hotkey_acpi_mask) < 0)
		pr_err("error while attempting to reset the event firmware interface\n");

	tpacpi_send_radiosw_update();
	hotkey_tablet_mode_notify_change();
	hotkey_wakeup_reason_notify_change();
	hotkey_wakeup_hotunplug_complete_notify_change();
	hotkey_poll_setup_safe(false);

	/* restore previous mode of adapive keyboard of X1 Carbon */
	if (tp_features.has_adaptive_kbd) {
		if (!acpi_evalf(hkey_handle, NULL, "STRW", "vd",
					adaptive_keyboard_prev_mode)) {
			pr_err("Cannot set adaptive keyboard mode.\n");
		}
	}
}