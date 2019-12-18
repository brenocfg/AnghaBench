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
struct recv_frame {int /*<<< orphan*/  list; int /*<<< orphan*/ * pkt; } ;
struct __queue {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int rtw_free_recvframe(struct recv_frame *precvframe,
		       struct __queue *pfree_recv_queue)
{
	if (!precvframe)
		return _FAIL;
	if (precvframe->pkt) {
		dev_kfree_skb_any(precvframe->pkt);/* free skb by driver */
		precvframe->pkt = NULL;
	}

	spin_lock_bh(&pfree_recv_queue->lock);

	list_del_init(&precvframe->list);

	list_add_tail(&precvframe->list, get_list_head(pfree_recv_queue));

	spin_unlock_bh(&pfree_recv_queue->lock);

	return _SUCCESS;
}