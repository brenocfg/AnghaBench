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
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/ * pkt; struct _adapter* adapter; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct recv_priv {int /*<<< orphan*/  free_recvframe_cnt; struct __queue free_recv_queue; } ;
struct _adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_free_recvframe(union recv_frame *precvframe,
		   struct  __queue *pfree_recv_queue)
{
	unsigned long irqL;
	struct _adapter *padapter = precvframe->u.hdr.adapter;
	struct recv_priv *precvpriv = &padapter->recvpriv;

	if (precvframe->u.hdr.pkt) {
		dev_kfree_skb_any(precvframe->u.hdr.pkt);/*free skb by driver*/
		precvframe->u.hdr.pkt = NULL;
	}
	spin_lock_irqsave(&pfree_recv_queue->lock, irqL);
	list_del_init(&(precvframe->u.hdr.list));
	list_add_tail(&(precvframe->u.hdr.list), &pfree_recv_queue->queue);
	if (padapter) {
		if (pfree_recv_queue == &precvpriv->free_recv_queue)
			precvpriv->free_recvframe_cnt++;
	}
	spin_unlock_irqrestore(&pfree_recv_queue->lock, irqL);
}