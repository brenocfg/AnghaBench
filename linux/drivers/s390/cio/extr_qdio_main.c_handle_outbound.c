#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pci_out_enabled; int /*<<< orphan*/  timer; scalar_t__ use_cq; } ;
struct TYPE_5__ {TYPE_3__ out; } ;
struct qdio_q {TYPE_2__ u; TYPE_1__* irq_ptr; int /*<<< orphan*/  nr_buf_used; } ;
struct TYPE_4__ {unsigned int scan_threshold; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 unsigned int QDIO_FLAG_PCI_OUT ; 
 scalar_t__ QDIO_IQDIO_QFMT ; 
 scalar_t__ QDIO_IRQ_STATE_ACTIVE ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 unsigned char SLSB_CU_OUTPUT_PRIMED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fast_requeue ; 
 scalar_t__ get_buf_state (struct qdio_q*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  multicast_outbound (struct qdio_q*) ; 
 scalar_t__ need_siga_sync (struct qdio_q*) ; 
 int /*<<< orphan*/  outbound_call ; 
 int /*<<< orphan*/  outbound_queue_full ; 
 int /*<<< orphan*/  pci_request_int ; 
 int /*<<< orphan*/  prev_buf (int) ; 
 unsigned long qdio_aob_for_buffer (TYPE_3__*,int) ; 
 int qdio_kick_outbound_q (struct qdio_q*,unsigned long) ; 
 int qdio_siga_sync_q (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_tasklet_schedule (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_type (struct qdio_q*) ; 
 int set_buf_states (struct qdio_q*,int,unsigned char,int) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_outbound(struct qdio_q *q, unsigned int callflags,
			   int bufnr, int count)
{
	const unsigned int scan_threshold = q->irq_ptr->scan_threshold;
	unsigned char state = 0;
	int used, rc = 0;

	qperf_inc(q, outbound_call);

	count = set_buf_states(q, bufnr, SLSB_CU_OUTPUT_PRIMED, count);
	used = atomic_add_return(count, &q->nr_buf_used);

	if (used == QDIO_MAX_BUFFERS_PER_Q)
		qperf_inc(q, outbound_queue_full);

	if (callflags & QDIO_FLAG_PCI_OUT) {
		q->u.out.pci_out_enabled = 1;
		qperf_inc(q, pci_request_int);
	} else
		q->u.out.pci_out_enabled = 0;

	if (queue_type(q) == QDIO_IQDIO_QFMT) {
		unsigned long phys_aob = 0;

		/* One SIGA-W per buffer required for unicast HSI */
		WARN_ON_ONCE(count > 1 && !multicast_outbound(q));

		if (q->u.out.use_cq)
			phys_aob = qdio_aob_for_buffer(&q->u.out, bufnr);

		rc = qdio_kick_outbound_q(q, phys_aob);
	} else if (need_siga_sync(q)) {
		rc = qdio_siga_sync_q(q);
	} else if (count < QDIO_MAX_BUFFERS_PER_Q &&
		   get_buf_state(q, prev_buf(bufnr), &state, 0) > 0 &&
		   state == SLSB_CU_OUTPUT_PRIMED) {
		/* The previous buffer is not processed yet, tack on. */
		qperf_inc(q, fast_requeue);
	} else {
		rc = qdio_kick_outbound_q(q, 0);
	}

	/* Let drivers implement their own completion scanning: */
	if (!scan_threshold)
		return rc;

	/* in case of SIGA errors we must process the error immediately */
	if (used >= scan_threshold || rc)
		qdio_tasklet_schedule(q);
	else
		/* free the SBALs in case of no further traffic */
		if (!timer_pending(&q->u.out.timer) &&
		    likely(q->irq_ptr->state == QDIO_IRQ_STATE_ACTIVE))
			mod_timer(&q->u.out.timer, jiffies + HZ);
	return rc;
}