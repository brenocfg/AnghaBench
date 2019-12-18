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
struct otg_fsm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  otgsc; } ;

/* Variables and functions */
 int OTGSC_HA_DATA_PULSE ; 
 int OTGSC_INTSTS_MASK ; 
 int /*<<< orphan*/  b_data_pulse_tmr ; 
 int /*<<< orphan*/  fsl_otg_add_timer (struct otg_fsm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_otg_loc_conn (int) ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (int,int /*<<< orphan*/ *) ; 
 scalar_t__ srp_wait_done ; 
 TYPE_1__* usb_dr_regs ; 

void fsl_otg_start_pulse(struct otg_fsm *fsm)
{
	u32 tmp;

	srp_wait_done = 0;
#ifdef HA_DATA_PULSE
	tmp = fsl_readl(&usb_dr_regs->otgsc) & ~OTGSC_INTSTS_MASK;
	tmp |= OTGSC_HA_DATA_PULSE;
	fsl_writel(tmp, &usb_dr_regs->otgsc);
#else
	fsl_otg_loc_conn(1);
#endif

	fsl_otg_add_timer(fsm, b_data_pulse_tmr);
}