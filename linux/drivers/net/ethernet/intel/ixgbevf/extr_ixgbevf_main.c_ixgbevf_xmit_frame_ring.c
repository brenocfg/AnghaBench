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
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ixgbevf_tx_buffer {int gso_segs; struct sk_buff* skb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  tx_flags; int /*<<< orphan*/  bytecount; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_busy; } ;
struct ixgbevf_ring {size_t next_to_use; struct ixgbevf_tx_buffer* tx_buffer_info; TYPE_1__ tx_stats; } ;
struct ixgbevf_ipsec_tx_data {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {unsigned short nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 scalar_t__ DESC_NEEDED ; 
 int /*<<< orphan*/  IXGBE_TX_FLAGS_VLAN ; 
 int /*<<< orphan*/  IXGBE_TX_FLAGS_VLAN_SHIFT ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ TXD_USE_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ is_link_local_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbevf_ipsec_tx (struct ixgbevf_ring*,struct ixgbevf_tx_buffer*,struct ixgbevf_ipsec_tx_data*) ; 
 scalar_t__ ixgbevf_maybe_stop_tx (struct ixgbevf_ring*,scalar_t__) ; 
 int ixgbevf_tso (struct ixgbevf_ring*,struct ixgbevf_tx_buffer*,int /*<<< orphan*/ *,struct ixgbevf_ipsec_tx_data*) ; 
 int /*<<< orphan*/  ixgbevf_tx_csum (struct ixgbevf_ring*,struct ixgbevf_tx_buffer*,struct ixgbevf_ipsec_tx_data*) ; 
 int /*<<< orphan*/  ixgbevf_tx_map (struct ixgbevf_ring*,struct ixgbevf_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_get_protocol (struct sk_buff*) ; 
 scalar_t__ xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static int ixgbevf_xmit_frame_ring(struct sk_buff *skb,
				   struct ixgbevf_ring *tx_ring)
{
	struct ixgbevf_tx_buffer *first;
	int tso;
	u32 tx_flags = 0;
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	struct ixgbevf_ipsec_tx_data ipsec_tx = { 0 };
#if PAGE_SIZE > IXGBE_MAX_DATA_PER_TXD
	unsigned short f;
#endif
	u8 hdr_len = 0;
	u8 *dst_mac = skb_header_pointer(skb, 0, 0, NULL);

	if (!dst_mac || is_link_local_ether_addr(dst_mac)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	/* need: 1 descriptor per page * PAGE_SIZE/IXGBE_MAX_DATA_PER_TXD,
	 *       + 1 desc for skb_headlen/IXGBE_MAX_DATA_PER_TXD,
	 *       + 2 desc gap to keep tail from touching head,
	 *       + 1 desc for context descriptor,
	 * otherwise try next time
	 */
#if PAGE_SIZE > IXGBE_MAX_DATA_PER_TXD
	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		count += TXD_USE_COUNT(skb_frag_size(frag));
	}
#else
	count += skb_shinfo(skb)->nr_frags;
#endif
	if (ixgbevf_maybe_stop_tx(tx_ring, count + 3)) {
		tx_ring->tx_stats.tx_busy++;
		return NETDEV_TX_BUSY;
	}

	/* record the location of the first descriptor for this packet */
	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	if (skb_vlan_tag_present(skb)) {
		tx_flags |= skb_vlan_tag_get(skb);
		tx_flags <<= IXGBE_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IXGBE_TX_FLAGS_VLAN;
	}

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = vlan_get_protocol(skb);

#ifdef CONFIG_IXGBEVF_IPSEC
	if (xfrm_offload(skb) && !ixgbevf_ipsec_tx(tx_ring, first, &ipsec_tx))
		goto out_drop;
#endif
	tso = ixgbevf_tso(tx_ring, first, &hdr_len, &ipsec_tx);
	if (tso < 0)
		goto out_drop;
	else if (!tso)
		ixgbevf_tx_csum(tx_ring, first, &ipsec_tx);

	ixgbevf_tx_map(tx_ring, first, hdr_len);

	ixgbevf_maybe_stop_tx(tx_ring, DESC_NEEDED);

	return NETDEV_TX_OK;

out_drop:
	dev_kfree_skb_any(first->skb);
	first->skb = NULL;

	return NETDEV_TX_OK;
}