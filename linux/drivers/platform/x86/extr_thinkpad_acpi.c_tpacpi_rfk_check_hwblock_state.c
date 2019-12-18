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
 int TPACPI_RFK_RADIO_OFF ; 
 int hotkey_get_wlsw () ; 
 int /*<<< orphan*/  tpacpi_rfk_update_hwblock_state (int) ; 

__attribute__((used)) static bool tpacpi_rfk_check_hwblock_state(void)
{
	int res = hotkey_get_wlsw();
	int hw_blocked;

	/* When unknown or unsupported, we have to assume it is unblocked */
	if (res < 0)
		return false;

	hw_blocked = (res == TPACPI_RFK_RADIO_OFF);
	tpacpi_rfk_update_hwblock_state(hw_blocked);

	return hw_blocked;
}