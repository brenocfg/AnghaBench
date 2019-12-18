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
struct qp_broker_entry {int /*<<< orphan*/  saved_consume_q; TYPE_2__* consume_q; int /*<<< orphan*/  saved_produce_q; TYPE_1__* produce_q; } ;
struct TYPE_4__ {int /*<<< orphan*/ * saved_header; int /*<<< orphan*/ * q_header; } ;
struct TYPE_3__ {int /*<<< orphan*/ * saved_header; int /*<<< orphan*/ * q_header; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int qp_host_map_queues (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int qp_save_headers(struct qp_broker_entry *entry)
{
	int result;

	if (entry->produce_q->saved_header != NULL &&
	    entry->consume_q->saved_header != NULL) {
		/*
		 *  If the headers have already been saved, we don't need to do
		 *  it again, and we don't want to map in the headers
		 *  unnecessarily.
		 */

		return VMCI_SUCCESS;
	}

	if (NULL == entry->produce_q->q_header ||
	    NULL == entry->consume_q->q_header) {
		result = qp_host_map_queues(entry->produce_q, entry->consume_q);
		if (result < VMCI_SUCCESS)
			return result;
	}

	memcpy(&entry->saved_produce_q, entry->produce_q->q_header,
	       sizeof(entry->saved_produce_q));
	entry->produce_q->saved_header = &entry->saved_produce_q;
	memcpy(&entry->saved_consume_q, entry->consume_q->q_header,
	       sizeof(entry->saved_consume_q));
	entry->consume_q->saved_header = &entry->saved_consume_q;

	return VMCI_SUCCESS;
}