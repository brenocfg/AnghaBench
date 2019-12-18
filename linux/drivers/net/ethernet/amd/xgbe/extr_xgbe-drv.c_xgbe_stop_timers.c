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
struct xgbe_prv_data {unsigned int channel_count; struct xgbe_channel** channel; int /*<<< orphan*/  service_timer; } ;
struct xgbe_channel {int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_stop_timers(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i;

	del_timer_sync(&pdata->service_timer);

	for (i = 0; i < pdata->channel_count; i++) {
		channel = pdata->channel[i];
		if (!channel->tx_ring)
			break;

		del_timer_sync(&channel->tx_timer);
	}
}