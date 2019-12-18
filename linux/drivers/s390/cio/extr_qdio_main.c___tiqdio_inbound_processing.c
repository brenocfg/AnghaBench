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
struct qdio_q {unsigned int first_to_check; int /*<<< orphan*/  irq_ptr; } ;

/* Variables and functions */
 unsigned int add_buf (unsigned int,int) ; 
 scalar_t__ need_siga_sync (struct qdio_q*) ; 
 scalar_t__ need_siga_sync_after_ai (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_check_outbound_pci_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_inbound_q_done (struct qdio_q*,unsigned int) ; 
 int qdio_inbound_q_moved (struct qdio_q*,unsigned int) ; 
 int /*<<< orphan*/  qdio_kick_handler (struct qdio_q*,int) ; 
 int /*<<< orphan*/  qdio_stop_polling (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_sync_queues (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_tasklet_schedule (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_inbound ; 
 int /*<<< orphan*/  tasklet_inbound_resched ; 
 int /*<<< orphan*/  tasklet_inbound_resched2 ; 

__attribute__((used)) static void __tiqdio_inbound_processing(struct qdio_q *q)
{
	unsigned int start = q->first_to_check;
	int count;

	qperf_inc(q, tasklet_inbound);
	if (need_siga_sync(q) && need_siga_sync_after_ai(q))
		qdio_sync_queues(q);

	/* The interrupt could be caused by a PCI request: */
	qdio_check_outbound_pci_queues(q->irq_ptr);

	count = qdio_inbound_q_moved(q, start);
	if (count == 0)
		return;

	start = add_buf(start, count);
	q->first_to_check = start;
	qdio_kick_handler(q, count);

	if (!qdio_inbound_q_done(q, start)) {
		qperf_inc(q, tasklet_inbound_resched);
		if (!qdio_tasklet_schedule(q))
			return;
	}

	qdio_stop_polling(q);
	/*
	 * We need to check again to not lose initiative after
	 * resetting the ACK state.
	 */
	if (!qdio_inbound_q_done(q, start)) {
		qperf_inc(q, tasklet_inbound_resched2);
		qdio_tasklet_schedule(q);
	}
}