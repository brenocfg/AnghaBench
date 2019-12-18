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
struct TYPE_6__ {scalar_t__ frag_num; scalar_t__ hdrlen; scalar_t__ iv_len; int /*<<< orphan*/  icv_len; } ;
struct recv_frame_hdr {TYPE_3__ attrib; int /*<<< orphan*/  len; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  rx_tail; } ;
struct TYPE_5__ {struct recv_frame_hdr hdr; int /*<<< orphan*/  list; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  scalar_t__ u8 ;
struct list_head {int dummy; } ;
struct __queue {int dummy; } ;
struct TYPE_4__ {struct __queue free_recv_queue; } ;
struct adapter {TYPE_1__ recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 struct list_head* get_list_head (struct __queue*) ; 
 struct list_head* get_next (struct list_head*) ; 
 scalar_t__* get_recvframe_data (union recv_frame*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recvframe_pull (union recv_frame*,scalar_t__) ; 
 int /*<<< orphan*/  recvframe_pull_tail (union recv_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recvframe_put (union recv_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,struct __queue*) ; 
 int /*<<< orphan*/  rtw_free_recvframe_queue (struct __queue*,struct __queue*) ; 

__attribute__((used)) static union recv_frame *recvframe_defrag(struct adapter *adapter,
					  struct __queue *defrag_q)
{
	struct list_head	 *plist, *phead;
	u8 *data, wlanhdr_offset;
	u8 curfragnum;
	struct recv_frame_hdr *pfhdr, *pnfhdr;
	union recv_frame *prframe, *pnextrframe;
	struct __queue	*pfree_recv_queue;

	curfragnum = 0;
	pfree_recv_queue = &adapter->recvpriv.free_recv_queue;

	phead = get_list_head(defrag_q);
	plist = get_next(phead);
	prframe = (union recv_frame *)plist;
	pfhdr = &prframe->u.hdr;
	list_del_init(&(prframe->u.list));

	if (curfragnum != pfhdr->attrib.frag_num) {
		/* the first fragment number must be 0 */
		/* free the whole queue */
		rtw_free_recvframe(prframe, pfree_recv_queue);
		rtw_free_recvframe_queue(defrag_q, pfree_recv_queue);

		return NULL;
	}

	curfragnum++;

	plist = get_list_head(defrag_q);

	plist = get_next(plist);

	data = get_recvframe_data(prframe);

	while (phead != plist) {
		pnextrframe = (union recv_frame *)plist;
		pnfhdr = &pnextrframe->u.hdr;


		/* check the fragment sequence  (2nd ~n fragment frame) */

		if (curfragnum != pnfhdr->attrib.frag_num) {
			/* the fragment number must be increasing  (after decache) */
			/* release the defrag_q & prframe */
			rtw_free_recvframe(prframe, pfree_recv_queue);
			rtw_free_recvframe_queue(defrag_q, pfree_recv_queue);
			return NULL;
		}

		curfragnum++;

		/* copy the 2nd~n fragment frame's payload to the first fragment */
		/* get the 2nd~last fragment frame's payload */

		wlanhdr_offset = pnfhdr->attrib.hdrlen + pnfhdr->attrib.iv_len;

		recvframe_pull(pnextrframe, wlanhdr_offset);

		/* append  to first fragment frame's tail (if privacy frame, pull the ICV) */
		recvframe_pull_tail(prframe, pfhdr->attrib.icv_len);

		/* memcpy */
		memcpy(pfhdr->rx_tail, pnfhdr->rx_data, pnfhdr->len);

		recvframe_put(prframe, pnfhdr->len);

		pfhdr->attrib.icv_len = pnfhdr->attrib.icv_len;
		plist = get_next(plist);

	}

	/* free the defrag_q queue and return the prframe */
	rtw_free_recvframe_queue(defrag_q, pfree_recv_queue);

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("Performance defrag!!!!!\n"));

	return prframe;
}