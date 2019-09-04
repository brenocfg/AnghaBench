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
struct sk_buff {int dummy; } ;
struct sge_txq {unsigned int size; unsigned int in_use; int /*<<< orphan*/  stops; int /*<<< orphan*/  sendq; } ;
struct sge_qset {int /*<<< orphan*/  txq_stopped; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ should_restart_tx (struct sge_txq*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_and_clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 struct sge_qset* txq_to_qset (struct sge_txq*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int check_desc_avail(struct adapter *adap, struct sge_txq *q,
				   struct sk_buff *skb, unsigned int ndesc,
				   unsigned int qid)
{
	if (unlikely(!skb_queue_empty(&q->sendq))) {
	      addq_exit:__skb_queue_tail(&q->sendq, skb);
		return 1;
	}
	if (unlikely(q->size - q->in_use < ndesc)) {
		struct sge_qset *qs = txq_to_qset(q, qid);

		set_bit(qid, &qs->txq_stopped);
		smp_mb__after_atomic();

		if (should_restart_tx(q) &&
		    test_and_clear_bit(qid, &qs->txq_stopped))
			return 2;

		q->stops++;
		goto addq_exit;
	}
	return 0;
}