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
struct TYPE_4__ {int /*<<< orphan*/  list; scalar_t__ len; struct adapter* adapter; } ;
struct TYPE_3__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_1__ u; } ;
struct __queue {int /*<<< orphan*/  lock; } ;
struct recv_priv {int /*<<< orphan*/  free_recvframe_cnt; struct __queue free_recv_queue; } ;
struct adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_os_free_recvframe (union recv_frame*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int rtw_free_recvframe(union recv_frame *precvframe, struct __queue *pfree_recv_queue)
{
	struct adapter *padapter = precvframe->u.hdr.adapter;
	struct recv_priv *precvpriv = &padapter->recvpriv;

	rtw_os_free_recvframe(precvframe);


	spin_lock_bh(&pfree_recv_queue->lock);

	list_del_init(&(precvframe->u.hdr.list));

	precvframe->u.hdr.len = 0;

	list_add_tail(&(precvframe->u.hdr.list), get_list_head(pfree_recv_queue));

	if (padapter) {
		if (pfree_recv_queue == &precvpriv->free_recv_queue)
				precvpriv->free_recvframe_cnt++;
	}
	spin_unlock_bh(&pfree_recv_queue->lock);
	return _SUCCESS;
}