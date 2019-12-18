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
struct i40e_pf {int flags; int /*<<< orphan*/  ptp_reset_start; int /*<<< orphan*/  ptp_prev_hw_time; int /*<<< orphan*/  ptp_caps; } ;

/* Variables and functions */
 int I40E_FLAG_PTP ; 
 int /*<<< orphan*/  i40e_ptp_gettimex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 

void i40e_ptp_save_hw_time(struct i40e_pf *pf)
{
	/* don't try to access the PTP clock if it's not enabled */
	if (!(pf->flags & I40E_FLAG_PTP))
		return;

	i40e_ptp_gettimex(&pf->ptp_caps, &pf->ptp_prev_hw_time, NULL);
	/* Get a monotonic starting time for this reset */
	pf->ptp_reset_start = ktime_get();
}