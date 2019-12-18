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
struct ef4_tx_queue {int /*<<< orphan*/  txd; int /*<<< orphan*/ * buffer; struct ef4_channel* channel; } ;
struct ef4_rx_queue {int /*<<< orphan*/  slow_fill; int /*<<< orphan*/  rxd; int /*<<< orphan*/ * buffer; } ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ napi_id; int /*<<< orphan*/  napi_hash_node; } ;
struct ef4_channel {struct ef4_rx_queue rx_queue; struct ef4_tx_queue* tx_queue; int /*<<< orphan*/  eventq; TYPE_1__ napi_str; int /*<<< orphan*/ * napi_dev; } ;

/* Variables and functions */
 int EF4_TXQ_TYPES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_rx_slow_fill ; 
 struct ef4_channel* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ef4_channel *
ef4_copy_channel(const struct ef4_channel *old_channel)
{
	struct ef4_channel *channel;
	struct ef4_rx_queue *rx_queue;
	struct ef4_tx_queue *tx_queue;
	int j;

	channel = kmalloc(sizeof(*channel), GFP_KERNEL);
	if (!channel)
		return NULL;

	*channel = *old_channel;

	channel->napi_dev = NULL;
	INIT_HLIST_NODE(&channel->napi_str.napi_hash_node);
	channel->napi_str.napi_id = 0;
	channel->napi_str.state = 0;
	memset(&channel->eventq, 0, sizeof(channel->eventq));

	for (j = 0; j < EF4_TXQ_TYPES; j++) {
		tx_queue = &channel->tx_queue[j];
		if (tx_queue->channel)
			tx_queue->channel = channel;
		tx_queue->buffer = NULL;
		memset(&tx_queue->txd, 0, sizeof(tx_queue->txd));
	}

	rx_queue = &channel->rx_queue;
	rx_queue->buffer = NULL;
	memset(&rx_queue->rxd, 0, sizeof(rx_queue->rxd));
	timer_setup(&rx_queue->slow_fill, ef4_rx_slow_fill, 0);

	return channel;
}