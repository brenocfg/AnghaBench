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
typedef  void* u64 ;
struct sq_hdr_subdesc {scalar_t__ subdesc_type; size_t rsvd2; scalar_t__ subdesc_cnt; scalar_t__ dont_send; } ;
struct snd_queue {void** skbuff; void** xdp_page; scalar_t__ is_xdp; } ;
struct sk_buff {scalar_t__ len; } ;
struct page {int dummy; } ;
struct nicvf {int /*<<< orphan*/  hw_tso; TYPE_3__* pnicvf; TYPE_1__* qs; } ;
struct net_device {int dummy; } ;
struct cqe_send_t {size_t sq_idx; size_t sqe_ptr; scalar_t__ send_status; } ;
struct TYPE_6__ {struct sk_buff* ptp_skb; } ;
struct TYPE_5__ {int tx_flags; } ;
struct TYPE_4__ {struct snd_queue* sq; } ;

/* Variables and functions */
 scalar_t__ GET_SQ_DESC (struct snd_queue*,size_t) ; 
 int SKBTX_IN_PROGRESS ; 
 scalar_t__ SQ_DESC_TYPE_HEADER ; 
 int /*<<< orphan*/  napi_consume_skb (struct sk_buff*,int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_check_cqe_tx_errs (TYPE_3__*,struct cqe_send_t*) ; 
 int /*<<< orphan*/  nicvf_unmap_sndq_buffers (struct nicvf*,struct snd_queue*,size_t,scalar_t__) ; 
 int page_ref_count (struct page*) ; 
 int /*<<< orphan*/  prefetch (struct sk_buff*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void nicvf_snd_pkt_handler(struct net_device *netdev,
				  struct cqe_send_t *cqe_tx,
				  int budget, int *subdesc_cnt,
				  unsigned int *tx_pkts, unsigned int *tx_bytes)
{
	struct sk_buff *skb = NULL;
	struct page *page;
	struct nicvf *nic = netdev_priv(netdev);
	struct snd_queue *sq;
	struct sq_hdr_subdesc *hdr;
	struct sq_hdr_subdesc *tso_sqe;

	sq = &nic->qs->sq[cqe_tx->sq_idx];

	hdr = (struct sq_hdr_subdesc *)GET_SQ_DESC(sq, cqe_tx->sqe_ptr);
	if (hdr->subdesc_type != SQ_DESC_TYPE_HEADER)
		return;

	/* Check for errors */
	if (cqe_tx->send_status)
		nicvf_check_cqe_tx_errs(nic->pnicvf, cqe_tx);

	/* Is this a XDP designated Tx queue */
	if (sq->is_xdp) {
		page = (struct page *)sq->xdp_page[cqe_tx->sqe_ptr];
		/* Check if it's recycled page or else unmap DMA mapping */
		if (page && (page_ref_count(page) == 1))
			nicvf_unmap_sndq_buffers(nic, sq, cqe_tx->sqe_ptr,
						 hdr->subdesc_cnt);

		/* Release page reference for recycling */
		if (page)
			put_page(page);
		sq->xdp_page[cqe_tx->sqe_ptr] = (u64)NULL;
		*subdesc_cnt += hdr->subdesc_cnt + 1;
		return;
	}

	skb = (struct sk_buff *)sq->skbuff[cqe_tx->sqe_ptr];
	if (skb) {
		/* Check for dummy descriptor used for HW TSO offload on 88xx */
		if (hdr->dont_send) {
			/* Get actual TSO descriptors and free them */
			tso_sqe =
			 (struct sq_hdr_subdesc *)GET_SQ_DESC(sq, hdr->rsvd2);
			nicvf_unmap_sndq_buffers(nic, sq, hdr->rsvd2,
						 tso_sqe->subdesc_cnt);
			*subdesc_cnt += tso_sqe->subdesc_cnt + 1;
		} else {
			nicvf_unmap_sndq_buffers(nic, sq, cqe_tx->sqe_ptr,
						 hdr->subdesc_cnt);
		}
		*subdesc_cnt += hdr->subdesc_cnt + 1;
		prefetch(skb);
		(*tx_pkts)++;
		*tx_bytes += skb->len;
		/* If timestamp is requested for this skb, don't free it */
		if (skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS &&
		    !nic->pnicvf->ptp_skb)
			nic->pnicvf->ptp_skb = skb;
		else
			napi_consume_skb(skb, budget);
		sq->skbuff[cqe_tx->sqe_ptr] = (u64)NULL;
	} else {
		/* In case of SW TSO on 88xx, only last segment will have
		 * a SKB attached, so just free SQEs here.
		 */
		if (!nic->hw_tso)
			*subdesc_cnt += hdr->subdesc_cnt + 1;
	}
}