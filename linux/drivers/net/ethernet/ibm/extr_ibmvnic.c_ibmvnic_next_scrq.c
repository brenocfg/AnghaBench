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
struct TYPE_2__ {int first; } ;
union sub_crq {TYPE_1__ generic; } ;
struct ibmvnic_sub_crq_queue {size_t cur; size_t size; int /*<<< orphan*/  lock; union sub_crq* msgs; } ;
struct ibmvnic_adapter {int dummy; } ;

/* Variables and functions */
 int IBMVNIC_CRQ_CMD_RSP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static union sub_crq *ibmvnic_next_scrq(struct ibmvnic_adapter *adapter,
					struct ibmvnic_sub_crq_queue *scrq)
{
	union sub_crq *entry;
	unsigned long flags;

	spin_lock_irqsave(&scrq->lock, flags);
	entry = &scrq->msgs[scrq->cur];
	if (entry->generic.first & IBMVNIC_CRQ_CMD_RSP) {
		if (++scrq->cur == scrq->size)
			scrq->cur = 0;
	} else {
		entry = NULL;
	}
	spin_unlock_irqrestore(&scrq->lock, flags);

	return entry;
}