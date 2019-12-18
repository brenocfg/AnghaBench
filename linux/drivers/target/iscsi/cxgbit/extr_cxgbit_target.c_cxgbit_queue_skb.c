#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct cxgbit_sock {int /*<<< orphan*/  txq; int /*<<< orphan*/  ppodq; int /*<<< orphan*/  write_seq; int /*<<< orphan*/  lock; scalar_t__ lock_owner; TYPE_1__ com; int /*<<< orphan*/  ack_waitq; } ;

/* Variables and functions */
 scalar_t__ CSK_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  cxgbit_lock_sock (struct cxgbit_sock*) ; 
 int /*<<< orphan*/  cxgbit_push_tx_frames (struct cxgbit_sock*) ; 
 scalar_t__ cxgbit_skcb_tx_extralen (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbit_unlock_sock (struct cxgbit_sock*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgbit_queue_skb(struct cxgbit_sock *csk, struct sk_buff *skb)
{
	int ret = 0;

	wait_event_interruptible(csk->ack_waitq, cxgbit_lock_sock(csk));

	if (unlikely((csk->com.state != CSK_STATE_ESTABLISHED) ||
		     signal_pending(current))) {
		__kfree_skb(skb);
		__skb_queue_purge(&csk->ppodq);
		ret = -1;
		spin_lock_bh(&csk->lock);
		if (csk->lock_owner) {
			spin_unlock_bh(&csk->lock);
			goto unlock;
		}
		spin_unlock_bh(&csk->lock);
		return ret;
	}

	csk->write_seq += skb->len +
			  cxgbit_skcb_tx_extralen(skb);

	skb_queue_splice_tail_init(&csk->ppodq, &csk->txq);
	__skb_queue_tail(&csk->txq, skb);
	cxgbit_push_tx_frames(csk);

unlock:
	cxgbit_unlock_sock(csk);
	return ret;
}