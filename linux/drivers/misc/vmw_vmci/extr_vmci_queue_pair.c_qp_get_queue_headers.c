#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmci_queue_header {int dummy; } ;
struct vmci_qp {TYPE_2__* consume_q; TYPE_1__* produce_q; } ;
struct TYPE_4__ {struct vmci_queue_header* saved_header; struct vmci_queue_header* q_header; } ;
struct TYPE_3__ {struct vmci_queue_header* saved_header; struct vmci_queue_header* q_header; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int qp_map_queue_headers (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int qp_get_queue_headers(const struct vmci_qp *qpair,
				struct vmci_queue_header **produce_q_header,
				struct vmci_queue_header **consume_q_header)
{
	int result;

	result = qp_map_queue_headers(qpair->produce_q, qpair->consume_q);
	if (result == VMCI_SUCCESS) {
		*produce_q_header = qpair->produce_q->q_header;
		*consume_q_header = qpair->consume_q->q_header;
	} else if (qpair->produce_q->saved_header &&
		   qpair->consume_q->saved_header) {
		*produce_q_header = qpair->produce_q->saved_header;
		*consume_q_header = qpair->consume_q->saved_header;
		result = VMCI_SUCCESS;
	}

	return result;
}