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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ ip_summed; int csum_level; int /*<<< orphan*/  protocol; } ;
struct qlcnic_rx_buffer {int dummy; } ;
struct qlcnic_recv_context {struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_sds_ring {int /*<<< orphan*/  napi; } ;
struct qlcnic_host_rds_ring {int num_desc; int skb_size; struct qlcnic_rx_buffer* rx_buf_arr; } ;
struct TYPE_2__ {int rxbytes; int /*<<< orphan*/  rx_pkts; int /*<<< orphan*/  encap_rx_csummed; int /*<<< orphan*/  rxdropped; } ;
struct qlcnic_adapter {size_t max_rds_rings; TYPE_1__ stats; scalar_t__ rx_mac_learn; struct qlcnic_recv_context* recv_ctx; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int qlcnic_83xx_csum_status (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_hndl (int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_is_lb_pkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_83xx_pktln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_add_lb_filter (struct qlcnic_adapter*,struct sk_buff*,int,int) ; 
 int qlcnic_check_rx_tagging (struct qlcnic_adapter*,struct sk_buff*,int*) ; 
 scalar_t__ qlcnic_encap_length (int /*<<< orphan*/ ) ; 
 struct sk_buff* qlcnic_process_rxbuf (struct qlcnic_adapter*,struct qlcnic_host_rds_ring*,int,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct qlcnic_rx_buffer *
qlcnic_83xx_process_rcv(struct qlcnic_adapter *adapter,
			struct qlcnic_host_sds_ring *sds_ring,
			u8 ring, u64 sts_data[])
{
	struct net_device *netdev = adapter->netdev;
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	struct qlcnic_rx_buffer *buffer;
	struct sk_buff *skb;
	struct qlcnic_host_rds_ring *rds_ring;
	int index, length, cksum, is_lb_pkt;
	u16 vid = 0xffff;
	int err;

	if (unlikely(ring >= adapter->max_rds_rings))
		return NULL;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_83xx_hndl(sts_data[0]);
	if (unlikely(index >= rds_ring->num_desc))
		return NULL;

	buffer = &rds_ring->rx_buf_arr[index];
	length = qlcnic_83xx_pktln(sts_data[0]);
	cksum  = qlcnic_83xx_csum_status(sts_data[1]);
	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, cksum);
	if (!skb)
		return buffer;

	if (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	else
		skb_put(skb, length);

	err = qlcnic_check_rx_tagging(adapter, skb, &vid);

	if (adapter->rx_mac_learn) {
		is_lb_pkt = qlcnic_83xx_is_lb_pkt(sts_data[1], 0);
		qlcnic_add_lb_filter(adapter, skb, is_lb_pkt, vid);
	}

	if (unlikely(err)) {
		adapter->stats.rxdropped++;
		dev_kfree_skb(skb);
		return buffer;
	}

	skb->protocol = eth_type_trans(skb, netdev);

	if (qlcnic_encap_length(sts_data[1]) &&
	    skb->ip_summed == CHECKSUM_UNNECESSARY) {
		skb->csum_level = 1;
		adapter->stats.encap_rx_csummed++;
	}

	if (vid != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);

	napi_gro_receive(&sds_ring->napi, skb);

	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	return buffer;
}