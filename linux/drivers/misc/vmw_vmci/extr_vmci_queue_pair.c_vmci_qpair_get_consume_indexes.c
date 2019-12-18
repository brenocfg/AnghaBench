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
typedef  scalar_t__ u64 ;
struct vmci_queue_header {int dummy; } ;
struct vmci_qp {scalar_t__ consume_q_size; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_INVALID_SIZE ; 
 int VMCI_SUCCESS ; 
 int qp_get_queue_headers (struct vmci_qp const*,struct vmci_queue_header**,struct vmci_queue_header**) ; 
 int /*<<< orphan*/  qp_lock (struct vmci_qp const*) ; 
 int /*<<< orphan*/  qp_unlock (struct vmci_qp const*) ; 
 int /*<<< orphan*/  vmci_q_header_get_pointers (struct vmci_queue_header*,struct vmci_queue_header*,scalar_t__*,scalar_t__*) ; 

int vmci_qpair_get_consume_indexes(const struct vmci_qp *qpair,
				   u64 *consumer_tail,
				   u64 *producer_head)
{
	struct vmci_queue_header *produce_q_header;
	struct vmci_queue_header *consume_q_header;
	int result;

	if (!qpair)
		return VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	if (result == VMCI_SUCCESS)
		vmci_q_header_get_pointers(consume_q_header, produce_q_header,
					   consumer_tail, producer_head);
	qp_unlock(qpair);

	if (result == VMCI_SUCCESS &&
	    ((consumer_tail && *consumer_tail >= qpair->consume_q_size) ||
	     (producer_head && *producer_head >= qpair->consume_q_size)))
		return VMCI_ERROR_INVALID_SIZE;

	return result;
}