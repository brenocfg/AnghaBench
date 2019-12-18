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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int data; int /*<<< orphan*/  encapsulation; } ;
struct nfp_net_tx_desc {int l3_offset; int l4_offset; int lso_hdrlen; int /*<<< orphan*/  flags; int /*<<< orphan*/  mss; } ;
struct nfp_net_tx_buf {int pkt_cnt; int real_len; } ;
struct nfp_net_r_vector {int /*<<< orphan*/  tx_sync; int /*<<< orphan*/  tx_lso; } ;
struct TYPE_2__ {int gso_segs; int gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_DESC_TX_LSO ; 
 int PCIE_DESC_TX_MSS_MASK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int inner_tcp_hdrlen (struct sk_buff*) ; 
 int skb_inner_network_offset (struct sk_buff*) ; 
 int skb_inner_transport_header (struct sk_buff*) ; 
 int skb_inner_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_tx_tso(struct nfp_net_r_vector *r_vec,
			   struct nfp_net_tx_buf *txbuf,
			   struct nfp_net_tx_desc *txd, struct sk_buff *skb,
			   u32 md_bytes)
{
	u32 l3_offset, l4_offset, hdrlen;
	u16 mss;

	if (!skb_is_gso(skb))
		return;

	if (!skb->encapsulation) {
		l3_offset = skb_network_offset(skb);
		l4_offset = skb_transport_offset(skb);
		hdrlen = skb_transport_offset(skb) + tcp_hdrlen(skb);
	} else {
		l3_offset = skb_inner_network_offset(skb);
		l4_offset = skb_inner_transport_offset(skb);
		hdrlen = skb_inner_transport_header(skb) - skb->data +
			inner_tcp_hdrlen(skb);
	}

	txbuf->pkt_cnt = skb_shinfo(skb)->gso_segs;
	txbuf->real_len += hdrlen * (txbuf->pkt_cnt - 1);

	mss = skb_shinfo(skb)->gso_size & PCIE_DESC_TX_MSS_MASK;
	txd->l3_offset = l3_offset - md_bytes;
	txd->l4_offset = l4_offset - md_bytes;
	txd->lso_hdrlen = hdrlen - md_bytes;
	txd->mss = cpu_to_le16(mss);
	txd->flags |= PCIE_DESC_TX_LSO;

	u64_stats_update_begin(&r_vec->tx_sync);
	r_vec->tx_lso++;
	u64_stats_update_end(&r_vec->tx_sync);
}