#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mfrag; scalar_t__ frag_num; scalar_t__ privacy; scalar_t__* ta; } ;
struct recv_frame_hdr {TYPE_3__ attrib; int /*<<< orphan*/  list; } ;
struct TYPE_8__ {struct recv_frame_hdr hdr; } ;
union recv_frame {TYPE_4__ u; } ;
typedef  scalar_t__ u8 ;
struct sta_priv {int dummy; } ;
struct list_head {int dummy; } ;
struct __queue {struct list_head queue; } ;
struct TYPE_6__ {struct __queue defrag_q; } ;
struct sta_info {TYPE_2__ sta_recvpriv; } ;
struct TYPE_5__ {struct __queue free_recv_queue; } ;
struct _adapter {TYPE_1__ recvpriv; struct sta_priv stapriv; } ;

/* Variables and functions */
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  r8712_free_recvframe (union recv_frame*,struct __queue*) ; 
 int /*<<< orphan*/  r8712_free_recvframe_queue (struct __queue*,struct __queue*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,scalar_t__*) ; 
 scalar_t__ r8712_recvframe_chkmic (struct _adapter*,union recv_frame*) ; 
 union recv_frame* recvframe_defrag (struct _adapter*,struct __queue*) ; 

union recv_frame *r8712_recvframe_chk_defrag(struct _adapter *padapter,
					     union recv_frame *precv_frame)
{
	u8	ismfrag;
	u8	fragnum;
	u8   *psta_addr;
	struct recv_frame_hdr *pfhdr;
	struct sta_info *psta;
	struct	sta_priv *pstapriv;
	struct list_head *phead;
	union recv_frame *prtnframe = NULL;
	struct  __queue *pfree_recv_queue, *pdefrag_q;

	pstapriv = &padapter->stapriv;
	pfhdr = &precv_frame->u.hdr;
	pfree_recv_queue = &padapter->recvpriv.free_recv_queue;
	/* need to define struct of wlan header frame ctrl */
	ismfrag = pfhdr->attrib.mfrag;
	fragnum = pfhdr->attrib.frag_num;
	psta_addr = pfhdr->attrib.ta;
	psta = r8712_get_stainfo(pstapriv, psta_addr);
	if (!psta)
		pdefrag_q = NULL;
	else
		pdefrag_q = &psta->sta_recvpriv.defrag_q;

	if ((ismfrag == 0) && (fragnum == 0))
		prtnframe = precv_frame;/*isn't a fragment frame*/
	if (ismfrag == 1) {
		/* 0~(n-1) fragment frame
		 * enqueue to defraf_g
		 */
		if (pdefrag_q) {
			if (fragnum == 0) {
				/*the first fragment*/
				if (!list_empty(&pdefrag_q->queue)) {
					/*free current defrag_q */
					r8712_free_recvframe_queue(pdefrag_q,
							     pfree_recv_queue);
				}
			}
			/* Then enqueue the 0~(n-1) fragment to the defrag_q */
			phead = &pdefrag_q->queue;
			list_add_tail(&pfhdr->list, phead);
			prtnframe = NULL;
		} else {
			/* can't find this ta's defrag_queue, so free this
			 * recv_frame
			 */
			r8712_free_recvframe(precv_frame, pfree_recv_queue);
			prtnframe = NULL;
		}

	}
	if ((ismfrag == 0) && (fragnum != 0)) {
		/* the last fragment frame
		 * enqueue the last fragment
		 */
		if (pdefrag_q) {
			phead = &pdefrag_q->queue;
			list_add_tail(&pfhdr->list, phead);
			/*call recvframe_defrag to defrag*/
			precv_frame = recvframe_defrag(padapter, pdefrag_q);
			prtnframe = precv_frame;
		} else {
			/* can't find this ta's defrag_queue, so free this
			 *  recv_frame
			 */
			r8712_free_recvframe(precv_frame, pfree_recv_queue);
			prtnframe = NULL;
		}
	}
	if (prtnframe && (prtnframe->u.hdr.attrib.privacy)) {
		/* after defrag we must check tkip mic code */
		if (r8712_recvframe_chkmic(padapter, prtnframe) == _FAIL) {
			r8712_free_recvframe(prtnframe, pfree_recv_queue);
			prtnframe = NULL;
		}
	}
	return prtnframe;
}