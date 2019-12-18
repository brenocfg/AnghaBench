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
struct TYPE_2__ {scalar_t__ first; } ;
union ibmvnic_crq {TYPE_1__ generic; } ;
struct ibmvnic_crq_queue {int /*<<< orphan*/  lock; } ;
struct ibmvnic_adapter {int wait_capability; int /*<<< orphan*/  running_cap_crqs; struct ibmvnic_crq_queue crq; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibmvnic_handle_crq (union ibmvnic_crq*,struct ibmvnic_adapter*) ; 
 union ibmvnic_crq* ibmvnic_next_crq (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ibmvnic_tasklet(void *data)
{
	struct ibmvnic_adapter *adapter = data;
	struct ibmvnic_crq_queue *queue = &adapter->crq;
	union ibmvnic_crq *crq;
	unsigned long flags;
	bool done = false;

	spin_lock_irqsave(&queue->lock, flags);
	while (!done) {
		/* Pull all the valid messages off the CRQ */
		while ((crq = ibmvnic_next_crq(adapter)) != NULL) {
			ibmvnic_handle_crq(crq, adapter);
			crq->generic.first = 0;
		}

		/* remain in tasklet until all
		 * capabilities responses are received
		 */
		if (!adapter->wait_capability)
			done = true;
	}
	/* if capabilities CRQ's were sent in this tasklet, the following
	 * tasklet must wait until all responses are received
	 */
	if (atomic_read(&adapter->running_cap_crqs) != 0)
		adapter->wait_capability = true;
	spin_unlock_irqrestore(&queue->lock, flags);
}