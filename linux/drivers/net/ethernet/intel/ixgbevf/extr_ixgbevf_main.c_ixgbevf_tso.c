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
typedef  int u8 ;
typedef  int u32 ;
struct tcphdr {int doff; int /*<<< orphan*/  check; } ;
struct sk_buff {scalar_t__ ip_summed; unsigned char* data; int len; } ;
struct ixgbevf_tx_buffer {int tx_flags; int bytecount; int /*<<< orphan*/  gso_segs; int /*<<< orphan*/  protocol; struct sk_buff* skb; } ;
struct ixgbevf_ring {int dummy; } ;
struct ixgbevf_ipsec_tx_data {int pfsa; int flags; int trailer_len; } ;
struct ipv6hdr {scalar_t__ payload_len; } ;
struct iphdr {int version; int ihl; scalar_t__ tot_len; int /*<<< orphan*/  check; } ;
struct TYPE_2__ {int gso_type; int gso_size; int /*<<< orphan*/  gso_segs; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int IXGBE_ADVTXD_IDX_SHIFT ; 
 int IXGBE_ADVTXD_L4LEN_SHIFT ; 
 int IXGBE_ADVTXD_MACLEN_SHIFT ; 
 int IXGBE_ADVTXD_MSS_SHIFT ; 
 int IXGBE_ADVTXD_TUCMD_IPV4 ; 
 int IXGBE_ADVTXD_TUCMD_L4T_TCP ; 
 int IXGBE_TX_FLAGS_CSUM ; 
 int IXGBE_TX_FLAGS_IPV4 ; 
 int IXGBE_TX_FLAGS_TSO ; 
 int IXGBE_TX_FLAGS_VLAN_MASK ; 
 int SKB_GSO_PARTIAL ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_replace_by_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_p_mpls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ixgbevf_tx_ctxtdesc (struct ixgbevf_ring*,int,int,int,int) ; 
 void* skb_checksum_start (struct sk_buff*) ; 
 int skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_inner_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int ixgbevf_tso(struct ixgbevf_ring *tx_ring,
		       struct ixgbevf_tx_buffer *first,
		       u8 *hdr_len,
		       struct ixgbevf_ipsec_tx_data *itd)
{
	u32 vlan_macip_lens, type_tucmd, mss_l4len_idx;
	struct sk_buff *skb = first->skb;
	union {
		struct iphdr *v4;
		struct ipv6hdr *v6;
		unsigned char *hdr;
	} ip;
	union {
		struct tcphdr *tcp;
		unsigned char *hdr;
	} l4;
	u32 paylen, l4_offset;
	u32 fceof_saidx = 0;
	int err;

	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return 0;

	if (!skb_is_gso(skb))
		return 0;

	err = skb_cow_head(skb, 0);
	if (err < 0)
		return err;

	if (eth_p_mpls(first->protocol))
		ip.hdr = skb_inner_network_header(skb);
	else
		ip.hdr = skb_network_header(skb);
	l4.hdr = skb_checksum_start(skb);

	/* ADV DTYP TUCMD MKRLOC/ISCSIHEDLEN */
	type_tucmd = IXGBE_ADVTXD_TUCMD_L4T_TCP;

	/* initialize outer IP header fields */
	if (ip.v4->version == 4) {
		unsigned char *csum_start = skb_checksum_start(skb);
		unsigned char *trans_start = ip.hdr + (ip.v4->ihl * 4);
		int len = csum_start - trans_start;

		/* IP header will have to cancel out any data that
		 * is not a part of the outer IP header, so set to
		 * a reverse csum if needed, else init check to 0.
		 */
		ip.v4->check = (skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) ?
					   csum_fold(csum_partial(trans_start,
								  len, 0)) : 0;
		type_tucmd |= IXGBE_ADVTXD_TUCMD_IPV4;

		ip.v4->tot_len = 0;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO |
				   IXGBE_TX_FLAGS_CSUM |
				   IXGBE_TX_FLAGS_IPV4;
	} else {
		ip.v6->payload_len = 0;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO |
				   IXGBE_TX_FLAGS_CSUM;
	}

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* compute length of segmentation header */
	*hdr_len = (l4.tcp->doff * 4) + l4_offset;

	/* remove payload length from inner checksum */
	paylen = skb->len - l4_offset;
	csum_replace_by_diff(&l4.tcp->check, htonl(paylen));

	/* update gso size and bytecount with header size */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* mss_l4len_id: use 1 as index for TSO */
	mss_l4len_idx = (*hdr_len - l4_offset) << IXGBE_ADVTXD_L4LEN_SHIFT;
	mss_l4len_idx |= skb_shinfo(skb)->gso_size << IXGBE_ADVTXD_MSS_SHIFT;
	mss_l4len_idx |= (1u << IXGBE_ADVTXD_IDX_SHIFT);

	fceof_saidx |= itd->pfsa;
	type_tucmd |= itd->flags | itd->trailer_len;

	/* vlan_macip_lens: HEADLEN, MACLEN, VLAN tag */
	vlan_macip_lens = l4.hdr - ip.hdr;
	vlan_macip_lens |= (ip.hdr - skb->data) << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	ixgbevf_tx_ctxtdesc(tx_ring, vlan_macip_lens, fceof_saidx, type_tucmd,
			    mss_l4len_idx);

	return 1;
}