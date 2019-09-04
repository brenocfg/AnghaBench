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
struct vmci_queue {scalar_t__ saved_header; int /*<<< orphan*/ * q_header; } ;

/* Variables and functions */
 int VMCI_ERROR_QUEUEPAIR_NOTATTACHED ; 
 int VMCI_ERROR_QUEUEPAIR_NOT_READY ; 
 int VMCI_SUCCESS ; 
 int qp_host_map_queues (struct vmci_queue*,struct vmci_queue*) ; 

__attribute__((used)) static int qp_map_queue_headers(struct vmci_queue *produce_q,
				struct vmci_queue *consume_q)
{
	int result;

	if (NULL == produce_q->q_header || NULL == consume_q->q_header) {
		result = qp_host_map_queues(produce_q, consume_q);
		if (result < VMCI_SUCCESS)
			return (produce_q->saved_header &&
				consume_q->saved_header) ?
			    VMCI_ERROR_QUEUEPAIR_NOT_READY :
			    VMCI_ERROR_QUEUEPAIR_NOTATTACHED;
	}

	return VMCI_SUCCESS;
}