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
 int /*<<< orphan*/  a_aidl_bdis_tmr ; 
 int /*<<< orphan*/  a_wait_bcon_tmr ; 
 int /*<<< orphan*/  a_wait_enum_tmr ; 
 int /*<<< orphan*/  a_wait_vrise_tmr ; 
 int /*<<< orphan*/  b_ase0_brst_tmr ; 
 int /*<<< orphan*/  b_data_pulse_tmr ; 
 int /*<<< orphan*/  b_se0_srp_tmr ; 
 int /*<<< orphan*/  b_srp_fail_tmr ; 
 int /*<<< orphan*/  b_srp_wait_tmr ; 
 int /*<<< orphan*/  b_vbus_pulse_tmr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void fsl_otg_uninit_timers(void)
{
	/* FSM used timers */
	kfree(a_wait_vrise_tmr);
	kfree(a_wait_bcon_tmr);
	kfree(a_aidl_bdis_tmr);
	kfree(b_ase0_brst_tmr);
	kfree(b_se0_srp_tmr);
	kfree(b_srp_fail_tmr);
	kfree(a_wait_enum_tmr);

	/* device driver used timers */
	kfree(b_srp_wait_tmr);
	kfree(b_data_pulse_tmr);
	kfree(b_vbus_pulse_tmr);
}