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
 unsigned int TPACPI_HOTKEY_MAP_LEN ; 
 unsigned int TP_ACPI_HOTKEYSCAN_ADAPTIVE_START ; 
 unsigned int TP_ACPI_HOTKEYSCAN_EXTENDED_START ; 
 int adaptive_keyboard_hotkey_notify_hotkey (unsigned int) ; 
 int hotkey_source_mask ; 
 int /*<<< orphan*/  tpacpi_input_send_key (unsigned int) ; 
 int /*<<< orphan*/  tpacpi_input_send_key_masked (unsigned int) ; 

__attribute__((used)) static bool hotkey_notify_hotkey(const u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
{
	/* 0x1000-0x1FFF: key presses */
	unsigned int scancode = hkey & 0xfff;
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	/*
	 * Original events are in the 0x10XX range, the adaptive keyboard
	 * found in 2014 X1 Carbon emits events are of 0x11XX. In 2017
	 * models, additional keys are emitted through 0x13XX.
	 */
	switch ((hkey >> 8) & 0xf) {
	case 0:
		if (scancode > 0 &&
		    scancode <= TP_ACPI_HOTKEYSCAN_ADAPTIVE_START) {
			/* HKEY event 0x1001 is scancode 0x00 */
			scancode--;
			if (!(hotkey_source_mask & (1 << scancode))) {
				tpacpi_input_send_key_masked(scancode);
				*send_acpi_ev = false;
			} else {
				*ignore_acpi_ev = true;
			}
			return true;
		}
		break;

	case 1:
		return adaptive_keyboard_hotkey_notify_hotkey(scancode);

	case 3:
		/* Extended keycodes start at 0x300 and our offset into the map
		 * TP_ACPI_HOTKEYSCAN_EXTENDED_START. The calculated scancode
		 * will be positive, but might not be in the correct range.
		 */
		scancode -= (0x300 - TP_ACPI_HOTKEYSCAN_EXTENDED_START);
		if (scancode >= TP_ACPI_HOTKEYSCAN_EXTENDED_START &&
		    scancode < TPACPI_HOTKEY_MAP_LEN) {
			tpacpi_input_send_key(scancode);
			return true;
		}
		break;
	}

	return false;
}