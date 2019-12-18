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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct vmpacket_descriptor {scalar_t__ trans_id; } ;
struct vmbus_channel {int /*<<< orphan*/  outbound; } ;
struct sk_buff {scalar_t__ cb; } ;
struct netvsc_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct netvsc_device {int /*<<< orphan*/  tx_disable; int /*<<< orphan*/  wait_drain; int /*<<< orphan*/  destroy; TYPE_1__* chan_table; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wake_queue; } ;
struct net_device_context {TYPE_2__ eth_stats; } ;
struct net_device {int dummy; } ;
struct hv_netvsc_packet {scalar_t__ send_buf_index; size_t q_idx; scalar_t__ total_bytes; scalar_t__ total_packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_sends; struct netvsc_stats tx_stats; } ;

/* Variables and functions */
 scalar_t__ NETVSC_INVALID_INDEX ; 
 scalar_t__ RING_AVAIL_PERCENT_HIWATER ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ hv_get_avail_to_write_percent (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_consume_skb (struct sk_buff*,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,size_t) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netvsc_free_send_slot (struct netvsc_device*,scalar_t__) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netvsc_send_tx_complete(struct net_device *ndev,
				    struct netvsc_device *net_device,
				    struct vmbus_channel *channel,
				    const struct vmpacket_descriptor *desc,
				    int budget)
{
	struct sk_buff *skb = (struct sk_buff *)(unsigned long)desc->trans_id;
	struct net_device_context *ndev_ctx = netdev_priv(ndev);
	u16 q_idx = 0;
	int queue_sends;

	/* Notify the layer above us */
	if (likely(skb)) {
		const struct hv_netvsc_packet *packet
			= (struct hv_netvsc_packet *)skb->cb;
		u32 send_index = packet->send_buf_index;
		struct netvsc_stats *tx_stats;

		if (send_index != NETVSC_INVALID_INDEX)
			netvsc_free_send_slot(net_device, send_index);
		q_idx = packet->q_idx;

		tx_stats = &net_device->chan_table[q_idx].tx_stats;

		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->packets += packet->total_packets;
		tx_stats->bytes += packet->total_bytes;
		u64_stats_update_end(&tx_stats->syncp);

		napi_consume_skb(skb, budget);
	}

	queue_sends =
		atomic_dec_return(&net_device->chan_table[q_idx].queue_sends);

	if (unlikely(net_device->destroy)) {
		if (queue_sends == 0)
			wake_up(&net_device->wait_drain);
	} else {
		struct netdev_queue *txq = netdev_get_tx_queue(ndev, q_idx);

		if (netif_tx_queue_stopped(txq) && !net_device->tx_disable &&
		    (hv_get_avail_to_write_percent(&channel->outbound) >
		     RING_AVAIL_PERCENT_HIWATER || queue_sends < 1)) {
			netif_tx_wake_queue(txq);
			ndev_ctx->eth_stats.wake_queue++;
		}
	}
}