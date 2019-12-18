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
struct i40e_pf {int /*<<< orphan*/  ptp_prev_hw_time; int /*<<< orphan*/  ptp_caps; int /*<<< orphan*/  ptp_reset_start; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_ptp_settime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec64_add_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void i40e_ptp_restore_hw_time(struct i40e_pf *pf)
{
	ktime_t delta = ktime_sub(ktime_get(), pf->ptp_reset_start);

	/* Update the previous HW time with the ktime delta */
	timespec64_add_ns(&pf->ptp_prev_hw_time, ktime_to_ns(delta));

	/* Restore the hardware clock registers */
	i40e_ptp_settime(&pf->ptp_caps, &pf->ptp_prev_hw_time);
}