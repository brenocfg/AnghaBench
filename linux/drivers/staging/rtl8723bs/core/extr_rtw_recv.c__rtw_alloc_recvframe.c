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
struct TYPE_3__ {struct adapter* adapter; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int /*<<< orphan*/  queue; } ;
struct recv_priv {int /*<<< orphan*/  free_recvframe_cnt; struct __queue free_recv_queue; } ;
struct list_head {int dummy; } ;
struct adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 struct list_head* get_list_head (struct __queue*) ; 
 struct list_head* get_next (struct list_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

union recv_frame *_rtw_alloc_recvframe(struct __queue *pfree_recv_queue)
{

	union recv_frame  *precvframe;
	struct list_head	*plist, *phead;
	struct adapter *padapter;
	struct recv_priv *precvpriv;

	if (list_empty(&pfree_recv_queue->queue))
		precvframe = NULL;
	else {
		phead = get_list_head(pfree_recv_queue);

		plist = get_next(phead);

		precvframe = (union recv_frame *)plist;

		list_del_init(&precvframe->u.hdr.list);
		padapter = precvframe->u.hdr.adapter;
		if (padapter) {
			precvpriv = &padapter->recvpriv;
			if (pfree_recv_queue == &precvpriv->free_recv_queue)
				precvpriv->free_recvframe_cnt--;
		}
	}
	return precvframe;
}