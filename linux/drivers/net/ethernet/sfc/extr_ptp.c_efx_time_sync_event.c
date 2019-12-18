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
struct TYPE_2__ {int sync_event_minor_shift; } ;
struct efx_ptp_data {TYPE_1__ nic_time; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;
struct efx_channel {int sync_timestamp_major; int sync_timestamp_minor; int /*<<< orphan*/  sync_events_state; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int MCDI_EVENT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTP_TIME_MAJOR ; 
 int /*<<< orphan*/  PTP_TIME_MINOR_MS_8BITS ; 
 int /*<<< orphan*/  SYNC_EVENTS_REQUESTED ; 
 int /*<<< orphan*/  SYNC_EVENTS_VALID ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void efx_time_sync_event(struct efx_channel *channel, efx_qword_t *ev)
{
	struct efx_nic *efx = channel->efx;
	struct efx_ptp_data *ptp = efx->ptp_data;

	/* When extracting the sync timestamp minor value, we should discard
	 * the least significant two bits. These are not required in order
	 * to reconstruct full-range timestamps and they are optionally used
	 * to report status depending on the options supplied when subscribing
	 * for sync events.
	 */
	channel->sync_timestamp_major = MCDI_EVENT_FIELD(*ev, PTP_TIME_MAJOR);
	channel->sync_timestamp_minor =
		(MCDI_EVENT_FIELD(*ev, PTP_TIME_MINOR_MS_8BITS) & 0xFC)
			<< ptp->nic_time.sync_event_minor_shift;

	/* if sync events have been disabled then we want to silently ignore
	 * this event, so throw away result.
	 */
	(void) cmpxchg(&channel->sync_events_state, SYNC_EVENTS_REQUESTED,
		       SYNC_EVENTS_VALID);
}