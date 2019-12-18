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
struct efx_nic {int dummy; } ;
typedef  struct efx_channel efx_channel ;

/* Variables and functions */
 int efx_ef10_rx_disable_timestamping (struct efx_channel*,int) ; 
 int efx_ef10_rx_enable_timestamping (struct efx_channel*,int) ; 
 struct efx_channel* efx_ptp_channel (struct efx_nic*) ; 

__attribute__((used)) static int efx_ef10_ptp_set_ts_sync_events(struct efx_nic *efx, bool en,
					   bool temp)
{
	int (*set)(struct efx_channel *channel, bool temp);
	struct efx_channel *channel;

	set = en ?
	      efx_ef10_rx_enable_timestamping :
	      efx_ef10_rx_disable_timestamping;

	channel = efx_ptp_channel(efx);
	if (channel) {
		int rc = set(channel, temp);
		if (en && rc != 0) {
			efx_ef10_ptp_set_ts_sync_events(efx, false, temp);
			return rc;
		}
	}

	return 0;
}