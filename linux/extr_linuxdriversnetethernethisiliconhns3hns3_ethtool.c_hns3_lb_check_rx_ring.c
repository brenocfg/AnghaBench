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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct hns3_nic_priv {TYPE_1__* ring_data; struct hnae3_handle* ae_handle; } ;
struct hns3_enet_ring_group {scalar_t__ total_packets; } ;
struct hns3_enet_ring {TYPE_2__* tqp_vector; } ;
struct hnae3_knic_private_info {int num_tqps; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct TYPE_4__ {struct hns3_enet_ring_group rx_group; } ;
struct TYPE_3__ {struct hns3_enet_ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_clean_rx_ring (struct hns3_enet_ring*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_lb_check_skb_data ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static u32 hns3_lb_check_rx_ring(struct hns3_nic_priv *priv, u32 budget)
{
	struct hnae3_handle *h = priv->ae_handle;
	struct hnae3_knic_private_info *kinfo;
	u32 i, rcv_good_pkt_total = 0;

	kinfo = &h->kinfo;
	for (i = kinfo->num_tqps; i < kinfo->num_tqps * 2; i++) {
		struct hns3_enet_ring *ring = priv->ring_data[i].ring;
		struct hns3_enet_ring_group *rx_group;
		u64 pre_rx_pkt;

		rx_group = &ring->tqp_vector->rx_group;
		pre_rx_pkt = rx_group->total_packets;

		preempt_disable();
		hns3_clean_rx_ring(ring, budget, hns3_lb_check_skb_data);
		preempt_enable();

		rcv_good_pkt_total += (rx_group->total_packets - pre_rx_pkt);
		rx_group->total_packets = pre_rx_pkt;
	}
	return rcv_good_pkt_total;
}