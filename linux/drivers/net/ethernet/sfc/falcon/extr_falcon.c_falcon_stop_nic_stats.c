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
struct falcon_nic_data {scalar_t__ stats_pending; int /*<<< orphan*/  stats_timer; int /*<<< orphan*/  stats_disable_count; } ;
struct ef4_nic {int /*<<< orphan*/  stats_lock; struct falcon_nic_data* nic_data; } ;

/* Variables and functions */
 scalar_t__ FALCON_XMAC_STATS_DMA_FLAG (struct ef4_nic*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  falcon_stats_complete (struct ef4_nic*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void falcon_stop_nic_stats(struct ef4_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	int i;

	might_sleep();

	spin_lock_bh(&efx->stats_lock);
	++nic_data->stats_disable_count;
	spin_unlock_bh(&efx->stats_lock);

	del_timer_sync(&nic_data->stats_timer);

	/* Wait enough time for the most recent transfer to
	 * complete. */
	for (i = 0; i < 4 && nic_data->stats_pending; i++) {
		if (FALCON_XMAC_STATS_DMA_FLAG(efx))
			break;
		msleep(1);
	}

	spin_lock_bh(&efx->stats_lock);
	falcon_stats_complete(efx);
	spin_unlock_bh(&efx->stats_lock);
}