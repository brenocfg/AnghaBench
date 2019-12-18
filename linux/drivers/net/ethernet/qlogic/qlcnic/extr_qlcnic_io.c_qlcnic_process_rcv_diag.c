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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct qlcnic_recv_context {struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_rds_ring {int num_desc; int skb_size; } ;
struct TYPE_4__ {int rxbytes; int /*<<< orphan*/  rx_pkts; } ;
struct qlcnic_adapter {int max_rds_rings; TYPE_2__ stats; TYPE_1__* ahw; int /*<<< orphan*/  mac_addr; struct qlcnic_recv_context* recv_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  diag_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dump_skb (struct sk_buff*,struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_check_loopback_buff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_get_sts_pkt_offset (int /*<<< orphan*/ ) ; 
 int qlcnic_get_sts_refhandle (int /*<<< orphan*/ ) ; 
 int qlcnic_get_sts_status (int /*<<< orphan*/ ) ; 
 int qlcnic_get_sts_totallength (int /*<<< orphan*/ ) ; 
 struct sk_buff* qlcnic_process_rxbuf (struct qlcnic_adapter*,struct qlcnic_host_rds_ring*,int,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qlcnic_process_rcv_diag(struct qlcnic_adapter *adapter, int ring,
				    u64 sts_data0)
{
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	struct sk_buff *skb;
	struct qlcnic_host_rds_ring *rds_ring;
	int index, length, cksum, pkt_offset;

	if (unlikely(ring >= adapter->max_rds_rings))
		return;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = qlcnic_get_sts_refhandle(sts_data0);
	length = qlcnic_get_sts_totallength(sts_data0);
	if (unlikely(index >= rds_ring->num_desc))
		return;

	cksum  = qlcnic_get_sts_status(sts_data0);
	pkt_offset = qlcnic_get_sts_pkt_offset(sts_data0);

	skb = qlcnic_process_rxbuf(adapter, rds_ring, index, cksum);
	if (!skb)
		return;

	if (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	else
		skb_put(skb, length);

	if (pkt_offset)
		skb_pull(skb, pkt_offset);

	if (!qlcnic_check_loopback_buff(skb->data, adapter->mac_addr))
		adapter->ahw->diag_cnt++;
	else
		dump_skb(skb, adapter);

	dev_kfree_skb_any(skb);
	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	return;
}