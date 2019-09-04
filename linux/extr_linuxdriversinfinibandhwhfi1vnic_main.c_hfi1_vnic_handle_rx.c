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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct hfi1_vnic_vport_info {int dummy; } ;
struct hfi1_vnic_rx_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; int /*<<< orphan*/  idx; struct hfi1_vnic_vport_info* vinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int hfi1_vnic_decap_skb (struct hfi1_vnic_rx_queue*,struct sk_buff*) ; 
 struct sk_buff* hfi1_vnic_get_skb (struct hfi1_vnic_rx_queue*) ; 
 int /*<<< orphan*/  hfi1_vnic_update_rx_counters (struct hfi1_vnic_vport_info*,int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hfi1_vnic_handle_rx(struct hfi1_vnic_rx_queue *rxq,
				int *work_done, int work_to_do)
{
	struct hfi1_vnic_vport_info *vinfo = rxq->vinfo;
	struct sk_buff *skb;
	int rc;

	while (1) {
		if (*work_done >= work_to_do)
			break;

		skb = hfi1_vnic_get_skb(rxq);
		if (unlikely(!skb))
			break;

		rc = hfi1_vnic_decap_skb(rxq, skb);
		/* update rx counters */
		hfi1_vnic_update_rx_counters(vinfo, rxq->idx, skb, rc);
		if (unlikely(rc)) {
			dev_kfree_skb_any(skb);
			continue;
		}

		skb_checksum_none_assert(skb);
		skb->protocol = eth_type_trans(skb, rxq->netdev);

		napi_gro_receive(&rxq->napi, skb);
		(*work_done)++;
	}
}