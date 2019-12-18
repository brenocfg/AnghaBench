#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  sub_channel_index; } ;
struct TYPE_6__ {TYPE_1__ offer; } ;
struct vmbus_channel {TYPE_2__ offermsg; } ;
struct sk_buff {scalar_t__ pkt_type; } ;
struct netvsc_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  multicast; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct netvsc_device {int dummy; } ;
struct TYPE_8__ {scalar_t__ pktlen; } ;
struct netvsc_channel {int /*<<< orphan*/  napi; TYPE_4__ rsc; struct netvsc_stats rx_stats; struct vmbus_channel* channel; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_no_memory; } ;
struct net_device_context {TYPE_3__ eth_stats; } ;
struct net_device {scalar_t__ reg_state; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int NVSP_STAT_FAIL ; 
 int NVSP_STAT_SUCCESS ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 struct sk_buff* netvsc_alloc_recv_skb (struct net_device*,struct netvsc_channel*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int netvsc_recv_callback(struct net_device *net,
			 struct netvsc_device *net_device,
			 struct netvsc_channel *nvchan)
{
	struct net_device_context *net_device_ctx = netdev_priv(net);
	struct vmbus_channel *channel = nvchan->channel;
	u16 q_idx = channel->offermsg.offer.sub_channel_index;
	struct sk_buff *skb;
	struct netvsc_stats *rx_stats;

	if (net->reg_state != NETREG_REGISTERED)
		return NVSP_STAT_FAIL;

	/* Allocate a skb - TODO direct I/O to pages? */
	skb = netvsc_alloc_recv_skb(net, nvchan);

	if (unlikely(!skb)) {
		++net_device_ctx->eth_stats.rx_no_memory;
		return NVSP_STAT_FAIL;
	}

	skb_record_rx_queue(skb, q_idx);

	/*
	 * Even if injecting the packet, record the statistics
	 * on the synthetic device because modifying the VF device
	 * statistics will not work correctly.
	 */
	rx_stats = &nvchan->rx_stats;
	u64_stats_update_begin(&rx_stats->syncp);
	rx_stats->packets++;
	rx_stats->bytes += nvchan->rsc.pktlen;

	if (skb->pkt_type == PACKET_BROADCAST)
		++rx_stats->broadcast;
	else if (skb->pkt_type == PACKET_MULTICAST)
		++rx_stats->multicast;
	u64_stats_update_end(&rx_stats->syncp);

	napi_gro_receive(&nvchan->napi, skb);
	return NVSP_STAT_SUCCESS;
}