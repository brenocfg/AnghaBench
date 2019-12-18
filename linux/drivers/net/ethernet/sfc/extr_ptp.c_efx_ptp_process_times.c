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
typedef  int u32 ;
struct timespec64 {scalar_t__ tv_nsec; int tv_sec; } ;
struct TYPE_3__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct pps_event_time {TYPE_1__ ts_real; } ;
struct efx_ptp_data {scalar_t__ min_synchronisation_ns; struct pps_event_time host_time_pps; TYPE_2__* timeset; int /*<<< orphan*/  (* nic_to_kernel_time ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  undersize_sync_windows; int /*<<< orphan*/  oversize_sync_windows; int /*<<< orphan*/  invalid_sync_windows; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_ptp_data* ptp_data; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {scalar_t__ window; int host_start; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  MCDI_DECLARE_STRUCT_PTR ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ MAX_SYNCHRONISATION_NS ; 
 int /*<<< orphan*/  MCDI_ARRAY_STRUCT_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int MCDI_VAR_ARRAY_LEN (size_t,int /*<<< orphan*/ ) ; 
 int MC_NANOSECOND_BITS ; 
 int MC_NANOSECOND_MASK ; 
 int MC_SECOND_MASK ; 
 int /*<<< orphan*/  PTP_OUT_SYNCHRONIZE_TIMESET ; 
 scalar_t__ SYNCHRONISATION_GRANULARITY_NS ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_ptp_read_timeset (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hw ; 
 struct timespec64 ktime_to_timespec64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pps_sub_ts (struct pps_event_time*,struct timespec64) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efx_ptp_process_times(struct efx_nic *efx, MCDI_DECLARE_STRUCT_PTR(synch_buf),
		      size_t response_length,
		      const struct pps_event_time *last_time)
{
	unsigned number_readings =
		MCDI_VAR_ARRAY_LEN(response_length,
				   PTP_OUT_SYNCHRONIZE_TIMESET);
	unsigned i;
	unsigned ngood = 0;
	unsigned last_good = 0;
	struct efx_ptp_data *ptp = efx->ptp_data;
	u32 last_sec;
	u32 start_sec;
	struct timespec64 delta;
	ktime_t mc_time;

	if (number_readings == 0)
		return -EAGAIN;

	/* Read the set of results and find the last good host-MC
	 * synchronization result. The MC times when it finishes reading the
	 * host time so the corrected window time should be fairly constant
	 * for a given platform. Increment stats for any results that appear
	 * to be erroneous.
	 */
	for (i = 0; i < number_readings; i++) {
		s32 window, corrected;
		struct timespec64 wait;

		efx_ptp_read_timeset(
			MCDI_ARRAY_STRUCT_PTR(synch_buf,
					      PTP_OUT_SYNCHRONIZE_TIMESET, i),
			&ptp->timeset[i]);

		wait = ktime_to_timespec64(
			ptp->nic_to_kernel_time(0, ptp->timeset[i].wait, 0));
		window = ptp->timeset[i].window;
		corrected = window - wait.tv_nsec;

		/* We expect the uncorrected synchronization window to be at
		 * least as large as the interval between host start and end
		 * times. If it is smaller than this then this is mostly likely
		 * to be a consequence of the host's time being adjusted.
		 * Check that the corrected sync window is in a reasonable
		 * range. If it is out of range it is likely to be because an
		 * interrupt or other delay occurred between reading the system
		 * time and writing it to MC memory.
		 */
		if (window < SYNCHRONISATION_GRANULARITY_NS) {
			++ptp->invalid_sync_windows;
		} else if (corrected >= MAX_SYNCHRONISATION_NS) {
			++ptp->oversize_sync_windows;
		} else if (corrected < ptp->min_synchronisation_ns) {
			++ptp->undersize_sync_windows;
		} else {
			ngood++;
			last_good = i;
		}
	}

	if (ngood == 0) {
		netif_warn(efx, drv, efx->net_dev,
			   "PTP no suitable synchronisations\n");
		return -EAGAIN;
	}

	/* Calculate delay from last good sync (host time) to last_time.
	 * It is possible that the seconds rolled over between taking
	 * the start reading and the last value written by the host.  The
	 * timescales are such that a gap of more than one second is never
	 * expected.  delta is *not* normalised.
	 */
	start_sec = ptp->timeset[last_good].host_start >> MC_NANOSECOND_BITS;
	last_sec = last_time->ts_real.tv_sec & MC_SECOND_MASK;
	if (start_sec != last_sec &&
	    ((start_sec + 1) & MC_SECOND_MASK) != last_sec) {
		netif_warn(efx, hw, efx->net_dev,
			   "PTP bad synchronisation seconds\n");
		return -EAGAIN;
	}
	delta.tv_sec = (last_sec - start_sec) & 1;
	delta.tv_nsec =
		last_time->ts_real.tv_nsec -
		(ptp->timeset[last_good].host_start & MC_NANOSECOND_MASK);

	/* Convert the NIC time at last good sync into kernel time.
	 * No correction is required - this time is the output of a
	 * firmware process.
	 */
	mc_time = ptp->nic_to_kernel_time(ptp->timeset[last_good].major,
					  ptp->timeset[last_good].minor, 0);

	/* Calculate delay from NIC top of second to last_time */
	delta.tv_nsec += ktime_to_timespec64(mc_time).tv_nsec;

	/* Set PPS timestamp to match NIC top of second */
	ptp->host_time_pps = *last_time;
	pps_sub_ts(&ptp->host_time_pps, delta);

	return 0;
}