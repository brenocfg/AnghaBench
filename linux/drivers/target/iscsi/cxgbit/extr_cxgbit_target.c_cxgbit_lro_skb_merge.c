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
typedef  size_t u8 ;
struct skb_shared_info {size_t nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {unsigned int len; unsigned int data_len; unsigned int truesize; } ;
struct cxgbit_sock {struct sk_buff* lro_hskb; } ;
struct cxgbit_lro_pdu_cb {int flags; size_t hfrag_idx; size_t dfrag_idx; size_t nr_dfrags; int /*<<< orphan*/  pdulen; int /*<<< orphan*/  ddigest; int /*<<< orphan*/  hlen; int /*<<< orphan*/  doffset; int /*<<< orphan*/  dlen; int /*<<< orphan*/  frags; int /*<<< orphan*/  hdr; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;

/* Variables and functions */
 int PDUCBF_RX_DATA ; 
 int PDUCBF_RX_DATA_DDPD ; 
 int PDUCBF_RX_HDR ; 
 int PDUCBF_RX_STATUS ; 
 struct cxgbit_lro_pdu_cb* cxgbit_skb_lro_pdu_cb (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void
cxgbit_lro_skb_merge(struct cxgbit_sock *csk, struct sk_buff *skb, u8 pdu_idx)
{
	struct sk_buff *hskb = csk->lro_hskb;
	struct cxgbit_lro_pdu_cb *hpdu_cb = cxgbit_skb_lro_pdu_cb(hskb, 0);
	struct cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, pdu_idx);
	struct skb_shared_info *hssi = skb_shinfo(hskb);
	struct skb_shared_info *ssi = skb_shinfo(skb);
	unsigned int len = 0;

	if (pdu_cb->flags & PDUCBF_RX_HDR) {
		u8 hfrag_idx = hssi->nr_frags;

		hpdu_cb->flags |= pdu_cb->flags;
		hpdu_cb->seq = pdu_cb->seq;
		hpdu_cb->hdr = pdu_cb->hdr;
		hpdu_cb->hlen = pdu_cb->hlen;

		memcpy(&hssi->frags[hfrag_idx], &ssi->frags[pdu_cb->hfrag_idx],
		       sizeof(skb_frag_t));

		get_page(skb_frag_page(&hssi->frags[hfrag_idx]));
		hssi->nr_frags++;
		hpdu_cb->frags++;
		hpdu_cb->hfrag_idx = hfrag_idx;

		len = skb_frag_size(&hssi->frags[hfrag_idx]);
		hskb->len += len;
		hskb->data_len += len;
		hskb->truesize += len;
	}

	if (pdu_cb->flags & PDUCBF_RX_DATA) {
		u8 dfrag_idx = hssi->nr_frags, i;

		hpdu_cb->flags |= pdu_cb->flags;
		hpdu_cb->dfrag_idx = dfrag_idx;

		len = 0;
		for (i = 0; i < pdu_cb->nr_dfrags; dfrag_idx++, i++) {
			memcpy(&hssi->frags[dfrag_idx],
			       &ssi->frags[pdu_cb->dfrag_idx + i],
			       sizeof(skb_frag_t));

			get_page(skb_frag_page(&hssi->frags[dfrag_idx]));

			len += skb_frag_size(&hssi->frags[dfrag_idx]);

			hssi->nr_frags++;
			hpdu_cb->frags++;
		}

		hpdu_cb->dlen = pdu_cb->dlen;
		hpdu_cb->doffset = hpdu_cb->hlen;
		hpdu_cb->nr_dfrags = pdu_cb->nr_dfrags;
		hskb->len += len;
		hskb->data_len += len;
		hskb->truesize += len;
	}

	if (pdu_cb->flags & PDUCBF_RX_STATUS) {
		hpdu_cb->flags |= pdu_cb->flags;

		if (hpdu_cb->flags & PDUCBF_RX_DATA)
			hpdu_cb->flags &= ~PDUCBF_RX_DATA_DDPD;

		hpdu_cb->ddigest = pdu_cb->ddigest;
		hpdu_cb->pdulen = pdu_cb->pdulen;
	}
}