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
 char AP_PWR_DOWN ; 
 char NVEC_SLEEP ; 
 int /*<<< orphan*/  nvec_power_handle ; 
 int /*<<< orphan*/  nvec_toggle_global_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvec_write_async (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void nvec_power_off(void)
{
	char ap_pwr_down[] = { NVEC_SLEEP, AP_PWR_DOWN };

	nvec_toggle_global_events(nvec_power_handle, false);
	nvec_write_async(nvec_power_handle, ap_pwr_down, 2);
}