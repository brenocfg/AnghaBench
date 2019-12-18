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
struct ef4_tx_queue {int queue; struct ef4_channel* channel; struct ef4_nic* efx; } ;
struct ef4_rx_queue {int /*<<< orphan*/  slow_fill; struct ef4_nic* efx; } ;
struct ef4_nic {int dummy; } ;
struct ef4_channel {int channel; struct ef4_rx_queue rx_queue; struct ef4_tx_queue* tx_queue; int /*<<< orphan*/ * type; struct ef4_nic* efx; } ;

/* Variables and functions */
 int EF4_TXQ_TYPES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ef4_default_channel_type ; 
 int /*<<< orphan*/  ef4_rx_slow_fill ; 
 struct ef4_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ef4_channel *
ef4_alloc_channel(struct ef4_nic *efx, int i, struct ef4_channel *old_channel)
{
	struct ef4_channel *channel;
	struct ef4_rx_queue *rx_queue;
	struct ef4_tx_queue *tx_queue;
	int j;

	channel = kzalloc(sizeof(*channel), GFP_KERNEL);
	if (!channel)
		return NULL;

	channel->efx = efx;
	channel->channel = i;
	channel->type = &ef4_default_channel_type;

	for (j = 0; j < EF4_TXQ_TYPES; j++) {
		tx_queue = &channel->tx_queue[j];
		tx_queue->efx = efx;
		tx_queue->queue = i * EF4_TXQ_TYPES + j;
		tx_queue->channel = channel;
	}

	rx_queue = &channel->rx_queue;
	rx_queue->efx = efx;
	timer_setup(&rx_queue->slow_fill, ef4_rx_slow_fill, 0);

	return channel;
}