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
struct ci_hdrc {scalar_t__ wq; } ;

/* Variables and functions */
 int OTGSC_INT_EN_BITS ; 
 int OTGSC_INT_STATUS_BITS ; 
 int /*<<< orphan*/  ci_hdrc_otg_fsm_remove (struct ci_hdrc*) ; 
 scalar_t__ ci_otg_is_fsm_mode (struct ci_hdrc*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  hw_write_otgsc (struct ci_hdrc*,int,int) ; 

void ci_hdrc_otg_destroy(struct ci_hdrc *ci)
{
	if (ci->wq) {
		flush_workqueue(ci->wq);
		destroy_workqueue(ci->wq);
	}
	/* Disable all OTG irq and clear status */
	hw_write_otgsc(ci, OTGSC_INT_EN_BITS | OTGSC_INT_STATUS_BITS,
						OTGSC_INT_STATUS_BITS);
	if (ci_otg_is_fsm_mode(ci))
		ci_hdrc_otg_fsm_remove(ci);
}