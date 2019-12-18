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
struct mlxsw_sp_ptp_clock {int /*<<< orphan*/  overflow_work; int /*<<< orphan*/  ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_ptp_clock*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 

void mlxsw_sp1_ptp_clock_fini(struct mlxsw_sp_ptp_clock *clock)
{
	ptp_clock_unregister(clock->ptp);
	cancel_delayed_work_sync(&clock->overflow_work);
	kfree(clock);
}