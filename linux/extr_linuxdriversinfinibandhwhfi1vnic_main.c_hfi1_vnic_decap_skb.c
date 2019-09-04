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
struct sk_buff {int len; } ;
struct hfi1_vnic_vport_info {TYPE_1__* stats; TYPE_2__* netdev; } ;
struct hfi1_vnic_rx_queue {size_t idx; struct hfi1_vnic_vport_info* vinfo; } ;
struct TYPE_4__ {int mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_runt; int /*<<< orphan*/  rx_oversize; } ;

/* Variables and functions */
 int EFAULT ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  OPA_VNIC_HDR_LEN ; 
 int VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int hfi1_vnic_decap_skb(struct hfi1_vnic_rx_queue *rxq,
				      struct sk_buff *skb)
{
	struct hfi1_vnic_vport_info *vinfo = rxq->vinfo;
	int max_len = vinfo->netdev->mtu + VLAN_ETH_HLEN;
	int rc = -EFAULT;

	skb_pull(skb, OPA_VNIC_HDR_LEN);

	/* Validate Packet length */
	if (unlikely(skb->len > max_len))
		vinfo->stats[rxq->idx].rx_oversize++;
	else if (unlikely(skb->len < ETH_ZLEN))
		vinfo->stats[rxq->idx].rx_runt++;
	else
		rc = 0;
	return rc;
}