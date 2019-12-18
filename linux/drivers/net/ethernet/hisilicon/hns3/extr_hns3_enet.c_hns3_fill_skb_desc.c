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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {int priority; scalar_t__ ip_summed; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_tso_err; int /*<<< orphan*/  tx_l2l3l4_err; int /*<<< orphan*/  tx_l4_proto_err; int /*<<< orphan*/  tx_vlan_err; } ;
struct hns3_enet_ring {int /*<<< orphan*/  syncp; TYPE_1__ stats; } ;
struct TYPE_4__ {void* outer_vlan_tag; void* vlan_tag; void* mss; void* paylen; void* type_cs_vlan_tso_len; void* ol_type_vlan_len_msec; } ;
struct hns3_desc {TYPE_2__ tx; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int HNS3_INNER_VLAN_TAG ; 
 int HNS3_OUTER_VLAN_TAG ; 
 int /*<<< orphan*/  HNS3_TXD_OVLAN_B ; 
 int /*<<< orphan*/  HNS3_TXD_VLAN_B ; 
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hns3_get_l4_protocol (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hns3_handle_vtags (struct hns3_enet_ring*,struct sk_buff*) ; 
 int /*<<< orphan*/  hns3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int hns3_set_l2l3l4 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hns3_set_tso (struct sk_buff*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns3_fill_skb_desc(struct hns3_enet_ring *ring,
			      struct sk_buff *skb, struct hns3_desc *desc)
{
	u32 ol_type_vlan_len_msec = 0;
	u32 type_cs_vlan_tso = 0;
	u32 paylen = skb->len;
	u16 inner_vtag = 0;
	u16 out_vtag = 0;
	u16 mss = 0;
	int ret;

	ret = hns3_handle_vtags(ring, skb);
	if (unlikely(ret < 0)) {
		u64_stats_update_begin(&ring->syncp);
		ring->stats.tx_vlan_err++;
		u64_stats_update_end(&ring->syncp);
		return ret;
	} else if (ret == HNS3_INNER_VLAN_TAG) {
		inner_vtag = skb_vlan_tag_get(skb);
		inner_vtag |= (skb->priority << VLAN_PRIO_SHIFT) &
				VLAN_PRIO_MASK;
		hns3_set_field(type_cs_vlan_tso, HNS3_TXD_VLAN_B, 1);
	} else if (ret == HNS3_OUTER_VLAN_TAG) {
		out_vtag = skb_vlan_tag_get(skb);
		out_vtag |= (skb->priority << VLAN_PRIO_SHIFT) &
				VLAN_PRIO_MASK;
		hns3_set_field(ol_type_vlan_len_msec, HNS3_TXD_OVLAN_B,
			       1);
	}

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		u8 ol4_proto, il4_proto;

		skb_reset_mac_len(skb);

		ret = hns3_get_l4_protocol(skb, &ol4_proto, &il4_proto);
		if (unlikely(ret)) {
			u64_stats_update_begin(&ring->syncp);
			ring->stats.tx_l4_proto_err++;
			u64_stats_update_end(&ring->syncp);
			return ret;
		}

		ret = hns3_set_l2l3l4(skb, ol4_proto, il4_proto,
				      &type_cs_vlan_tso,
				      &ol_type_vlan_len_msec);
		if (unlikely(ret)) {
			u64_stats_update_begin(&ring->syncp);
			ring->stats.tx_l2l3l4_err++;
			u64_stats_update_end(&ring->syncp);
			return ret;
		}

		ret = hns3_set_tso(skb, &paylen, &mss,
				   &type_cs_vlan_tso);
		if (unlikely(ret)) {
			u64_stats_update_begin(&ring->syncp);
			ring->stats.tx_tso_err++;
			u64_stats_update_end(&ring->syncp);
			return ret;
		}
	}

	/* Set txbd */
	desc->tx.ol_type_vlan_len_msec =
		cpu_to_le32(ol_type_vlan_len_msec);
	desc->tx.type_cs_vlan_tso_len = cpu_to_le32(type_cs_vlan_tso);
	desc->tx.paylen = cpu_to_le32(paylen);
	desc->tx.mss = cpu_to_le16(mss);
	desc->tx.vlan_tag = cpu_to_le16(inner_vtag);
	desc->tx.outer_vlan_tag = cpu_to_le16(out_vtag);

	return 0;
}