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
struct vmci_queue_header {int dummy; } ;
struct vmci_qp {int /*<<< orphan*/  consume_q_size; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ VMCI_ERROR_INVALID_ARGS ; 
 scalar_t__ VMCI_SUCCESS ; 
 scalar_t__ qp_get_queue_headers (struct vmci_qp const*,struct vmci_queue_header**,struct vmci_queue_header**) ; 
 int /*<<< orphan*/  qp_lock (struct vmci_qp const*) ; 
 int /*<<< orphan*/  qp_unlock (struct vmci_qp const*) ; 
 scalar_t__ vmci_q_header_free_space (struct vmci_queue_header*,struct vmci_queue_header*,int /*<<< orphan*/ ) ; 

s64 vmci_qpair_consume_free_space(const struct vmci_qp *qpair)
{
	struct vmci_queue_header *produce_q_header;
	struct vmci_queue_header *consume_q_header;
	s64 result;

	if (!qpair)
		return VMCI_ERROR_INVALID_ARGS;

	qp_lock(qpair);
	result =
	    qp_get_queue_headers(qpair, &produce_q_header, &consume_q_header);
	if (result == VMCI_SUCCESS)
		result = vmci_q_header_free_space(consume_q_header,
						  produce_q_header,
						  qpair->consume_q_size);
	else
		result = 0;

	qp_unlock(qpair);

	return result;
}