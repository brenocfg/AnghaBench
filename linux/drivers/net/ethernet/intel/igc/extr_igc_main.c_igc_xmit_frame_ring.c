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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct igc_tx_buffer {int gso_segs; int /*<<< orphan*/  protocol; int /*<<< orphan*/  tx_flags; int /*<<< orphan*/  bytecount; struct sk_buff* skb; } ;
struct igc_ring {size_t next_to_use; struct igc_tx_buffer* tx_buffer_info; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {unsigned short nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ TXD_USE_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ igc_maybe_stop_tx (struct igc_ring*,scalar_t__) ; 
 int /*<<< orphan*/  igc_tx_csum (struct igc_ring*,struct igc_tx_buffer*) ; 
 int /*<<< orphan*/  igc_tx_map (struct igc_ring*,struct igc_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t igc_xmit_frame_ring(struct sk_buff *skb,
				       struct igc_ring *tx_ring)
{
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	__be16 protocol = vlan_get_protocol(skb);
	struct igc_tx_buffer *first;
	u32 tx_flags = 0;
	unsigned short f;
	u8 hdr_len = 0;

	/* need: 1 descriptor per page * PAGE_SIZE/IGC_MAX_DATA_PER_TXD,
	 *	+ 1 desc for skb_headlen/IGC_MAX_DATA_PER_TXD,
	 *	+ 2 desc gap to keep tail from touching head,
	 *	+ 1 desc for context descriptor,
	 * otherwise try next time
	 */
	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		count += TXD_USE_COUNT(skb_frag_size(
						&skb_shinfo(skb)->frags[f]));

	if (igc_maybe_stop_tx(tx_ring, count + 3)) {
		/* this is a hard error */
		return NETDEV_TX_BUSY;
	}

	/* record the location of the first descriptor for this packet */
	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = protocol;

	igc_tx_csum(tx_ring, first);

	igc_tx_map(tx_ring, first, hdr_len);

	return NETDEV_TX_OK;
}