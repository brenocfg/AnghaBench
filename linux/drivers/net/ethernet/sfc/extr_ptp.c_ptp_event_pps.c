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
struct efx_ptp_data {int /*<<< orphan*/  pps_work; int /*<<< orphan*/  pps_workwq; scalar_t__ nic_ts_enabled; } ;
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ptp_event_pps(struct efx_nic *efx, struct efx_ptp_data *ptp)
{
	if (ptp->nic_ts_enabled)
		queue_work(ptp->pps_workwq, &ptp->pps_work);
}