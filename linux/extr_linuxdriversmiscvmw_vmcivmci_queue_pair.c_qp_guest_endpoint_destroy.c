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
struct TYPE_2__ {int /*<<< orphan*/  consume_size; int /*<<< orphan*/  produce_size; } ;
struct qp_guest_endpoint {int /*<<< orphan*/  resource; TYPE_1__ qp; int /*<<< orphan*/  consume_q; int /*<<< orphan*/  produce_q; int /*<<< orphan*/  ppn_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qp_guest_endpoint*) ; 
 int /*<<< orphan*/  qp_cleanup_queue_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_free_ppn_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_free_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_resource_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qp_guest_endpoint_destroy(struct qp_guest_endpoint *entry)
{
	qp_free_ppn_set(&entry->ppn_set);
	qp_cleanup_queue_mutex(entry->produce_q, entry->consume_q);
	qp_free_queue(entry->produce_q, entry->qp.produce_size);
	qp_free_queue(entry->consume_q, entry->qp.consume_size);
	/* Unlink from resource hash table and free callback */
	vmci_resource_remove(&entry->resource);

	kfree(entry);
}