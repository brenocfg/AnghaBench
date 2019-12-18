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
typedef  int u16 ;
struct sk_buff {int offload_fwd_mark; scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct rocker_tlv {int dummy; } ;
struct rocker_port {TYPE_2__* dev; } ;
struct rocker_desc_info {int dummy; } ;
struct rocker {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ROCKER_RX_FLAGS_FWD_OFFLOAD ; 
 size_t ROCKER_TLV_RX_FLAGS ; 
 size_t ROCKER_TLV_RX_FRAG_LEN ; 
 int /*<<< orphan*/  ROCKER_TLV_RX_MAX ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 struct sk_buff* rocker_desc_cookie_ptr_get (struct rocker_desc_info*) ; 
 int rocker_dma_rx_ring_skb_alloc (struct rocker_port const*,struct rocker_desc_info*) ; 
 int /*<<< orphan*/  rocker_dma_rx_ring_skb_unmap (struct rocker const*,struct rocker_tlv const**) ; 
 void* rocker_tlv_get_u16 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_desc (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_desc_info*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 

__attribute__((used)) static int rocker_port_rx_proc(const struct rocker *rocker,
			       const struct rocker_port *rocker_port,
			       struct rocker_desc_info *desc_info)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_RX_MAX + 1];
	struct sk_buff *skb = rocker_desc_cookie_ptr_get(desc_info);
	size_t rx_len;
	u16 rx_flags = 0;

	if (!skb)
		return -ENOENT;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_RX_MAX, desc_info);
	if (!attrs[ROCKER_TLV_RX_FRAG_LEN])
		return -EINVAL;
	if (attrs[ROCKER_TLV_RX_FLAGS])
		rx_flags = rocker_tlv_get_u16(attrs[ROCKER_TLV_RX_FLAGS]);

	rocker_dma_rx_ring_skb_unmap(rocker, attrs);

	rx_len = rocker_tlv_get_u16(attrs[ROCKER_TLV_RX_FRAG_LEN]);
	skb_put(skb, rx_len);
	skb->protocol = eth_type_trans(skb, rocker_port->dev);

	if (rx_flags & ROCKER_RX_FLAGS_FWD_OFFLOAD)
		skb->offload_fwd_mark = 1;

	rocker_port->dev->stats.rx_packets++;
	rocker_port->dev->stats.rx_bytes += skb->len;

	netif_receive_skb(skb);

	return rocker_dma_rx_ring_skb_alloc(rocker_port, desc_info);
}