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
typedef  int u64 ;

/* Variables and functions */
 int OPAL_PM_WINKLE_ENABLED ; 
 int /*<<< orphan*/  SPRN_HID0 ; 
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  opal_slw_set_reg (int,int /*<<< orphan*/ ,int) ; 
 int pnv_get_supported_cpuidle_states () ; 

__attribute__((used)) static void update_hid_in_slw(u64 hid0)
{
	u64 idle_states = pnv_get_supported_cpuidle_states();

	if (idle_states & OPAL_PM_WINKLE_ENABLED) {
		/* OPAL call to patch slw with the new HID0 value */
		u64 cpu_pir = hard_smp_processor_id();

		opal_slw_set_reg(cpu_pir, SPRN_HID0, hid0);
	}
}