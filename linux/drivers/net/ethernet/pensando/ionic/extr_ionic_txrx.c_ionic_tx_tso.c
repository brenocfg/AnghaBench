#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  unsigned int u16 ;
struct sk_buff {unsigned int len; int encapsulation; unsigned int data; } ;
struct ionic_txq_sg_elem {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct ionic_txq_desc {int dummy; } ;
struct ionic_tx_stats {int /*<<< orphan*/  tso; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; int /*<<< orphan*/  frags; } ;
struct ionic_queue {struct ionic_desc_info* head; TYPE_2__* lif; } ;
struct ionic_desc_info {scalar_t__ desc; struct ionic_desc_info* next; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {unsigned int gso_size; unsigned int nr_frags; int gso_type; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {TYPE_1__* ionic; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SKB_GSO_GRE_CSUM ; 
 int SKB_GSO_UDP_TUNNEL_CSUM ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 unsigned int inner_tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  ionic_tx_clean (struct ionic_queue*,struct ionic_desc_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ionic_tx_map_frag (struct ionic_queue*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ionic_tx_map_single (struct ionic_queue*,unsigned int,unsigned int) ; 
 int ionic_tx_tcp_inner_pseudo_csum (struct sk_buff*) ; 
 int ionic_tx_tcp_pseudo_csum (struct sk_buff*) ; 
 struct ionic_txq_desc* ionic_tx_tso_next (struct ionic_queue*,struct ionic_txq_sg_elem**) ; 
 int /*<<< orphan*/  ionic_tx_tso_post (struct ionic_queue*,struct ionic_txq_desc*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int,unsigned int,int,unsigned int,int,int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct ionic_tx_stats* q_to_tx_stats (struct ionic_queue*) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 unsigned int skb_inner_transport_header (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 unsigned int skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static int ionic_tx_tso(struct ionic_queue *q, struct sk_buff *skb)
{
	struct ionic_tx_stats *stats = q_to_tx_stats(q);
	struct ionic_desc_info *abort = q->head;
	struct device *dev = q->lif->ionic->dev;
	struct ionic_desc_info *rewind = abort;
	struct ionic_txq_sg_elem *elem;
	struct ionic_txq_desc *desc;
	unsigned int frag_left = 0;
	unsigned int offset = 0;
	unsigned int len_left;
	dma_addr_t desc_addr;
	unsigned int hdrlen;
	unsigned int nfrags;
	unsigned int seglen;
	u64 total_bytes = 0;
	u64 total_pkts = 0;
	unsigned int left;
	unsigned int len;
	unsigned int mss;
	skb_frag_t *frag;
	bool start, done;
	bool outer_csum;
	bool has_vlan;
	u16 desc_len;
	u8 desc_nsge;
	u16 vlan_tci;
	bool encap;
	int err;

	mss = skb_shinfo(skb)->gso_size;
	nfrags = skb_shinfo(skb)->nr_frags;
	len_left = skb->len - skb_headlen(skb);
	outer_csum = (skb_shinfo(skb)->gso_type & SKB_GSO_GRE_CSUM) ||
		     (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM);
	has_vlan = !!skb_vlan_tag_present(skb);
	vlan_tci = skb_vlan_tag_get(skb);
	encap = skb->encapsulation;

	/* Preload inner-most TCP csum field with IP pseudo hdr
	 * calculated with IP length set to zero.  HW will later
	 * add in length to each TCP segment resulting from the TSO.
	 */

	if (encap)
		err = ionic_tx_tcp_inner_pseudo_csum(skb);
	else
		err = ionic_tx_tcp_pseudo_csum(skb);
	if (err)
		return err;

	if (encap)
		hdrlen = skb_inner_transport_header(skb) - skb->data +
			 inner_tcp_hdrlen(skb);
	else
		hdrlen = skb_transport_offset(skb) + tcp_hdrlen(skb);

	seglen = hdrlen + mss;
	left = skb_headlen(skb);

	desc = ionic_tx_tso_next(q, &elem);
	start = true;

	/* Chop skb->data up into desc segments */

	while (left > 0) {
		len = min(seglen, left);
		frag_left = seglen - len;
		desc_addr = ionic_tx_map_single(q, skb->data + offset, len);
		if (dma_mapping_error(dev, desc_addr))
			goto err_out_abort;
		desc_len = len;
		desc_nsge = 0;
		left -= len;
		offset += len;
		if (nfrags > 0 && frag_left > 0)
			continue;
		done = (nfrags == 0 && left == 0);
		ionic_tx_tso_post(q, desc, skb,
				  desc_addr, desc_nsge, desc_len,
				  hdrlen, mss,
				  outer_csum,
				  vlan_tci, has_vlan,
				  start, done);
		total_pkts++;
		total_bytes += start ? len : len + hdrlen;
		desc = ionic_tx_tso_next(q, &elem);
		start = false;
		seglen = mss;
	}

	/* Chop skb frags into desc segments */

	for (frag = skb_shinfo(skb)->frags; len_left; frag++) {
		offset = 0;
		left = skb_frag_size(frag);
		len_left -= left;
		nfrags--;
		stats->frags++;

		while (left > 0) {
			if (frag_left > 0) {
				len = min(frag_left, left);
				frag_left -= len;
				elem->addr =
				    cpu_to_le64(ionic_tx_map_frag(q, frag,
								  offset, len));
				if (dma_mapping_error(dev, elem->addr))
					goto err_out_abort;
				elem->len = cpu_to_le16(len);
				elem++;
				desc_nsge++;
				left -= len;
				offset += len;
				if (nfrags > 0 && frag_left > 0)
					continue;
				done = (nfrags == 0 && left == 0);
				ionic_tx_tso_post(q, desc, skb, desc_addr,
						  desc_nsge, desc_len,
						  hdrlen, mss, outer_csum,
						  vlan_tci, has_vlan,
						  start, done);
				total_pkts++;
				total_bytes += start ? len : len + hdrlen;
				desc = ionic_tx_tso_next(q, &elem);
				start = false;
			} else {
				len = min(mss, left);
				frag_left = mss - len;
				desc_addr = ionic_tx_map_frag(q, frag,
							      offset, len);
				if (dma_mapping_error(dev, desc_addr))
					goto err_out_abort;
				desc_len = len;
				desc_nsge = 0;
				left -= len;
				offset += len;
				if (nfrags > 0 && frag_left > 0)
					continue;
				done = (nfrags == 0 && left == 0);
				ionic_tx_tso_post(q, desc, skb, desc_addr,
						  desc_nsge, desc_len,
						  hdrlen, mss, outer_csum,
						  vlan_tci, has_vlan,
						  start, done);
				total_pkts++;
				total_bytes += start ? len : len + hdrlen;
				desc = ionic_tx_tso_next(q, &elem);
				start = false;
			}
		}
	}

	stats->pkts += total_pkts;
	stats->bytes += total_bytes;
	stats->tso++;

	return 0;

err_out_abort:
	while (rewind->desc != q->head->desc) {
		ionic_tx_clean(q, rewind, NULL, NULL);
		rewind = rewind->next;
	}
	q->head = abort;

	return -ENOMEM;
}