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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct nx_host_sds_ring {int /*<<< orphan*/  napi; } ;
struct nx_host_rds_ring {int num_desc; int skb_size; struct netxen_rx_buffer* rx_buf_arr; } ;
struct netxen_rx_buffer {int dummy; } ;
struct netxen_recv_context {struct nx_host_rds_ring* rds_rings; } ;
struct TYPE_2__ {int rxbytes; int /*<<< orphan*/  rx_pkts; } ;
struct netxen_adapter {int max_rds_rings; TYPE_1__ stats; struct netxen_recv_context recv_ctx; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int netxen_get_sts_pkt_offset (int /*<<< orphan*/ ) ; 
 int netxen_get_sts_refhandle (int /*<<< orphan*/ ) ; 
 int netxen_get_sts_status (int /*<<< orphan*/ ) ; 
 int netxen_get_sts_totallength (int /*<<< orphan*/ ) ; 
 struct sk_buff* netxen_process_rxbuf (struct netxen_adapter*,struct nx_host_rds_ring*,int,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct netxen_rx_buffer *
netxen_process_rcv(struct netxen_adapter *adapter,
		struct nx_host_sds_ring *sds_ring,
		int ring, u64 sts_data0)
{
	struct net_device *netdev = adapter->netdev;
	struct netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	struct netxen_rx_buffer *buffer;
	struct sk_buff *skb;
	struct nx_host_rds_ring *rds_ring;
	int index, length, cksum, pkt_offset;

	if (unlikely(ring >= adapter->max_rds_rings))
		return NULL;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = netxen_get_sts_refhandle(sts_data0);
	if (unlikely(index >= rds_ring->num_desc))
		return NULL;

	buffer = &rds_ring->rx_buf_arr[index];

	length = netxen_get_sts_totallength(sts_data0);
	cksum  = netxen_get_sts_status(sts_data0);
	pkt_offset = netxen_get_sts_pkt_offset(sts_data0);

	skb = netxen_process_rxbuf(adapter, rds_ring, index, cksum);
	if (!skb)
		return buffer;

	if (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	else
		skb_put(skb, length);


	if (pkt_offset)
		skb_pull(skb, pkt_offset);

	skb->protocol = eth_type_trans(skb, netdev);

	napi_gro_receive(&sds_ring->napi, skb);

	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	return buffer;
}