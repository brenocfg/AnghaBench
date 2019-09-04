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
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_service_timer ; 
 int /*<<< orphan*/  xgbe_tx_timer ; 

__attribute__((used)) static void xgbe_init_timers(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i;

	timer_setup(&pdata->service_timer, xgbe_service_timer, 0);

	for (i = 0; i < pdata->channel_count; i++) {
		channel = pdata->channel[i];
		if (!channel->tx_ring)
			break;

		timer_setup(&channel->tx_timer, xgbe_tx_timer, 0);
	}
}