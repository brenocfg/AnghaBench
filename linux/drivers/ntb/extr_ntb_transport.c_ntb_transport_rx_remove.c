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
struct ntb_transport_qp {int /*<<< orphan*/  rx_free_q; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  rx_pend_q; scalar_t__ client_ready; } ;
struct ntb_queue_entry {unsigned int len; int /*<<< orphan*/  entry; void* cb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *ntb_transport_rx_remove(struct ntb_transport_qp *qp, unsigned int *len)
{
	struct ntb_queue_entry *entry;
	void *buf;

	if (!qp || qp->client_ready)
		return NULL;

	entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_pend_q);
	if (!entry)
		return NULL;

	buf = entry->cb_data;
	*len = entry->len;

	ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry, &qp->rx_free_q);

	return buf;
}