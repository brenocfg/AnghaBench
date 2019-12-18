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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct iavf_tx_buffer {int gso_segs; struct sk_buff* skb; int /*<<< orphan*/  bytecount; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_busy; int /*<<< orphan*/  tx_linearize; } ;
struct iavf_ring {size_t next_to_use; struct iavf_tx_buffer* tx_bi; TYPE_1__ tx_stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IAVF_TX_DESC_CMD_ICRC ; 
 int /*<<< orphan*/  IAVF_TX_DESC_DTYPE_CONTEXT ; 
 int /*<<< orphan*/  IAVF_TX_FLAGS_IPV4 ; 
 int /*<<< orphan*/  IAVF_TX_FLAGS_IPV6 ; 
 int /*<<< orphan*/  IAVF_TX_FLAGS_TSO ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ iavf_chk_linearize (struct sk_buff*,int) ; 
 int /*<<< orphan*/  iavf_create_tx_ctx (struct iavf_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iavf_maybe_stop_tx (struct iavf_ring*,int) ; 
 int /*<<< orphan*/  iavf_trace (int /*<<< orphan*/ ,struct sk_buff*,struct iavf_ring*) ; 
 int iavf_tso (struct iavf_tx_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iavf_tx_enable_csum (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct iavf_ring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_tx_map (struct iavf_ring*,struct sk_buff*,struct iavf_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iavf_tx_prepare_vlan_flags (struct sk_buff*,struct iavf_ring*,int /*<<< orphan*/ *) ; 
 int iavf_txd_use_count (int /*<<< orphan*/ ) ; 
 int iavf_xmit_descriptor_count (struct sk_buff*) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 
 int /*<<< orphan*/  xmit_frame_ring ; 
 int /*<<< orphan*/  xmit_frame_ring_drop ; 

__attribute__((used)) static netdev_tx_t iavf_xmit_frame_ring(struct sk_buff *skb,
					struct iavf_ring *tx_ring)
{
	u64 cd_type_cmd_tso_mss = IAVF_TX_DESC_DTYPE_CONTEXT;
	u32 cd_tunneling = 0, cd_l2tag2 = 0;
	struct iavf_tx_buffer *first;
	u32 td_offset = 0;
	u32 tx_flags = 0;
	__be16 protocol;
	u32 td_cmd = 0;
	u8 hdr_len = 0;
	int tso, count;

	/* prefetch the data, we'll need it later */
	prefetch(skb->data);

	iavf_trace(xmit_frame_ring, skb, tx_ring);

	count = iavf_xmit_descriptor_count(skb);
	if (iavf_chk_linearize(skb, count)) {
		if (__skb_linearize(skb)) {
			dev_kfree_skb_any(skb);
			return NETDEV_TX_OK;
		}
		count = iavf_txd_use_count(skb->len);
		tx_ring->tx_stats.tx_linearize++;
	}

	/* need: 1 descriptor per page * PAGE_SIZE/IAVF_MAX_DATA_PER_TXD,
	 *       + 1 desc for skb_head_len/IAVF_MAX_DATA_PER_TXD,
	 *       + 4 desc gap to avoid the cache line where head is,
	 *       + 1 desc for context descriptor,
	 * otherwise try next time
	 */
	if (iavf_maybe_stop_tx(tx_ring, count + 4 + 1)) {
		tx_ring->tx_stats.tx_busy++;
		return NETDEV_TX_BUSY;
	}

	/* record the location of the first descriptor for this packet */
	first = &tx_ring->tx_bi[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	/* prepare the xmit flags */
	if (iavf_tx_prepare_vlan_flags(skb, tx_ring, &tx_flags))
		goto out_drop;

	/* obtain protocol of skb */
	protocol = vlan_get_protocol(skb);

	/* setup IPv4/IPv6 offloads */
	if (protocol == htons(ETH_P_IP))
		tx_flags |= IAVF_TX_FLAGS_IPV4;
	else if (protocol == htons(ETH_P_IPV6))
		tx_flags |= IAVF_TX_FLAGS_IPV6;

	tso = iavf_tso(first, &hdr_len, &cd_type_cmd_tso_mss);

	if (tso < 0)
		goto out_drop;
	else if (tso)
		tx_flags |= IAVF_TX_FLAGS_TSO;

	/* Always offload the checksum, since it's in the data descriptor */
	tso = iavf_tx_enable_csum(skb, &tx_flags, &td_cmd, &td_offset,
				  tx_ring, &cd_tunneling);
	if (tso < 0)
		goto out_drop;

	/* always enable CRC insertion offload */
	td_cmd |= IAVF_TX_DESC_CMD_ICRC;

	iavf_create_tx_ctx(tx_ring, cd_type_cmd_tso_mss,
			   cd_tunneling, cd_l2tag2);

	iavf_tx_map(tx_ring, skb, first, tx_flags, hdr_len,
		    td_cmd, td_offset);

	return NETDEV_TX_OK;

out_drop:
	iavf_trace(xmit_frame_ring_drop, first->skb, tx_ring);
	dev_kfree_skb_any(first->skb);
	first->skb = NULL;
	return NETDEV_TX_OK;
}