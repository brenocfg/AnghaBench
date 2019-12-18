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
struct TYPE_2__ {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  b_srp_wait_tmr ; 
 int /*<<< orphan*/  fsl_otg_add_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_otg_chrg_vbus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* fsl_otg_dev ; 
 int /*<<< orphan*/  fsl_otg_dischrg_vbus (int) ; 

void b_vbus_pulse_end(unsigned long foo)
{
	fsl_otg_chrg_vbus(&fsl_otg_dev->fsm, 0);

	/*
	 * As USB3300 using the same a_sess_vld and b_sess_vld voltage
	 * we need to discharge the bus for a while to distinguish
	 * residual voltage of vbus pulsing and A device pull up
	 */
	fsl_otg_dischrg_vbus(1);
	fsl_otg_add_timer(&fsl_otg_dev->fsm, b_srp_wait_tmr);
}