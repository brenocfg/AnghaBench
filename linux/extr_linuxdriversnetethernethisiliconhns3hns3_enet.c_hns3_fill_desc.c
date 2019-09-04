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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  len; } ;
struct hns3_enet_ring {size_t next_to_use; struct hns3_desc* desc; struct hns3_desc_cb* desc_cb; } ;
struct hns3_desc_cb {int length; int type; int /*<<< orphan*/  dma; void* priv; } ;
struct TYPE_2__ {void* outer_vlan_tag; void* vlan_tag; void* mss; void* paylen; void* type_cs_vlan_tso_len; void* ol_type_vlan_len_msec; void* bdtp_fe_sc_vld_ra_ri; void* send_size; } ;
struct hns3_desc {TYPE_1__ tx; int /*<<< orphan*/  addr; } ;
typedef  enum hns_desc_type { ____Placeholder_hns_desc_type } hns_desc_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int DESC_TYPE_SKB ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hns3_fill_desc_vtags (struct sk_buff*,struct hns3_enet_ring*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int hns3_get_l4_protocol (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns3_set_l2l3l4_len (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hns3_set_l3l4_type_csum (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hns3_set_tso (struct sk_buff*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns3_set_txbd_baseinfo (scalar_t__*,int) ; 
 int /*<<< orphan*/  next_to_use ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns3_fill_desc(struct hns3_enet_ring *ring, void *priv,
			  int size, dma_addr_t dma, int frag_end,
			  enum hns_desc_type type)
{
	struct hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	struct hns3_desc *desc = &ring->desc[ring->next_to_use];
	u32 ol_type_vlan_len_msec = 0;
	u16 bdtp_fe_sc_vld_ra_ri = 0;
	u32 type_cs_vlan_tso = 0;
	struct sk_buff *skb;
	u16 inner_vtag = 0;
	u16 out_vtag = 0;
	u32 paylen = 0;
	u16 mss = 0;
	u8 ol4_proto;
	u8 il4_proto;
	int ret;

	/* The txbd's baseinfo of DESC_TYPE_PAGE & DESC_TYPE_SKB */
	desc_cb->priv = priv;
	desc_cb->length = size;
	desc_cb->dma = dma;
	desc_cb->type = type;

	/* now, fill the descriptor */
	desc->addr = cpu_to_le64(dma);
	desc->tx.send_size = cpu_to_le16((u16)size);
	hns3_set_txbd_baseinfo(&bdtp_fe_sc_vld_ra_ri, frag_end);
	desc->tx.bdtp_fe_sc_vld_ra_ri = cpu_to_le16(bdtp_fe_sc_vld_ra_ri);

	if (type == DESC_TYPE_SKB) {
		skb = (struct sk_buff *)priv;
		paylen = skb->len;

		ret = hns3_fill_desc_vtags(skb, ring, &type_cs_vlan_tso,
					   &ol_type_vlan_len_msec,
					   &inner_vtag, &out_vtag);
		if (unlikely(ret))
			return ret;

		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			skb_reset_mac_len(skb);

			ret = hns3_get_l4_protocol(skb, &ol4_proto, &il4_proto);
			if (ret)
				return ret;
			hns3_set_l2l3l4_len(skb, ol4_proto, il4_proto,
					    &type_cs_vlan_tso,
					    &ol_type_vlan_len_msec);
			ret = hns3_set_l3l4_type_csum(skb, ol4_proto, il4_proto,
						      &type_cs_vlan_tso,
						      &ol_type_vlan_len_msec);
			if (ret)
				return ret;

			ret = hns3_set_tso(skb, &paylen, &mss,
					   &type_cs_vlan_tso);
			if (ret)
				return ret;
		}

		/* Set txbd */
		desc->tx.ol_type_vlan_len_msec =
			cpu_to_le32(ol_type_vlan_len_msec);
		desc->tx.type_cs_vlan_tso_len =
			cpu_to_le32(type_cs_vlan_tso);
		desc->tx.paylen = cpu_to_le32(paylen);
		desc->tx.mss = cpu_to_le16(mss);
		desc->tx.vlan_tag = cpu_to_le16(inner_vtag);
		desc->tx.outer_vlan_tag = cpu_to_le16(out_vtag);
	}

	/* move ring pointer to next.*/
	ring_ptr_move_fw(ring, next_to_use);

	return 0;
}