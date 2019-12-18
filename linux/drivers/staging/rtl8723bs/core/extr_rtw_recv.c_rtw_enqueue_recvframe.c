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
typedef  union recv_frame {int dummy; } recv_frame ;
struct __queue {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_enqueue_recvframe (union recv_frame*,struct __queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

sint rtw_enqueue_recvframe(union recv_frame *precvframe, struct __queue *queue)
{
	sint ret;

	/* _spinlock(&pfree_recv_queue->lock); */
	spin_lock_bh(&queue->lock);
	ret = _rtw_enqueue_recvframe(precvframe, queue);
	/* spin_unlock(&pfree_recv_queue->lock); */
	spin_unlock_bh(&queue->lock);

	return ret;
}