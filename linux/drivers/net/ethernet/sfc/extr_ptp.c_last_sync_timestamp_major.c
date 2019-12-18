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
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {int dummy; } ;
struct efx_channel {int /*<<< orphan*/  sync_timestamp_major; } ;

/* Variables and functions */
 struct efx_channel* efx_ptp_channel (struct efx_nic*) ; 

__attribute__((used)) static u32 last_sync_timestamp_major(struct efx_nic *efx)
{
	struct efx_channel *channel = efx_ptp_channel(efx);
	u32 major = 0;

	if (channel)
		major = channel->sync_timestamp_major;
	return major;
}