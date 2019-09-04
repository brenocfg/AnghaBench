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
 int /*<<< orphan*/  adj_time_work ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ hv_ptp_clock ; 
 int /*<<< orphan*/  ptp_clock_unregister (scalar_t__) ; 

__attribute__((used)) static void hv_timesync_deinit(void)
{
	if (hv_ptp_clock)
		ptp_clock_unregister(hv_ptp_clock);
	cancel_work_sync(&adj_time_work);
}