#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {unsigned int tv_sec; unsigned int tv_nsec; } ;
struct pps_event_time {struct timespec64 ts_real; } ;
struct TYPE_3__ {int* addr; } ;
struct efx_ptp_data {TYPE_1__ start; } ;
struct efx_nic {TYPE_2__* type; struct efx_ptp_data* ptp_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ptp_write_host_time ) (struct efx_nic*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int MC_NANOSECOND_BITS ; 
 scalar_t__ READ_ONCE (int) ; 
 int /*<<< orphan*/  SYNCHRONISATION_GRANULARITY_NS ; 
 int /*<<< orphan*/  SYNCHRONISE_PERIOD_NS ; 
 int /*<<< orphan*/  pps_get_ts (struct pps_event_time*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  timespec64_add_ns (struct timespec64*,int /*<<< orphan*/ ) ; 
 scalar_t__ timespec64_compare (struct timespec64*,struct timespec64*) ; 

__attribute__((used)) static void efx_ptp_send_times(struct efx_nic *efx,
			       struct pps_event_time *last_time)
{
	struct pps_event_time now;
	struct timespec64 limit;
	struct efx_ptp_data *ptp = efx->ptp_data;
	int *mc_running = ptp->start.addr;

	pps_get_ts(&now);
	limit = now.ts_real;
	timespec64_add_ns(&limit, SYNCHRONISE_PERIOD_NS);

	/* Write host time for specified period or until MC is done */
	while ((timespec64_compare(&now.ts_real, &limit) < 0) &&
	       READ_ONCE(*mc_running)) {
		struct timespec64 update_time;
		unsigned int host_time;

		/* Don't update continuously to avoid saturating the PCIe bus */
		update_time = now.ts_real;
		timespec64_add_ns(&update_time, SYNCHRONISATION_GRANULARITY_NS);
		do {
			pps_get_ts(&now);
		} while ((timespec64_compare(&now.ts_real, &update_time) < 0) &&
			 READ_ONCE(*mc_running));

		/* Synchronise NIC with single word of time only */
		host_time = (now.ts_real.tv_sec << MC_NANOSECOND_BITS |
			     now.ts_real.tv_nsec);
		/* Update host time in NIC memory */
		efx->type->ptp_write_host_time(efx, host_time);
	}
	*last_time = now;
}