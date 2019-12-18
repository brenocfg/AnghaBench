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

/* Variables and functions */
 union recv_frame* _rtw_alloc_recvframe (struct __queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

union recv_frame *rtw_alloc_recvframe(struct __queue *pfree_recv_queue)
{
	union recv_frame  *precvframe;

	spin_lock_bh(&pfree_recv_queue->lock);

	precvframe = _rtw_alloc_recvframe(pfree_recv_queue);

	spin_unlock_bh(&pfree_recv_queue->lock);

	return precvframe;
}