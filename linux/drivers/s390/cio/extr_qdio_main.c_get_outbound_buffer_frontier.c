#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nr_sbal_nop; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_cq; } ;
struct TYPE_7__ {TYPE_1__ out; } ;
struct qdio_q {int /*<<< orphan*/  nr; TYPE_4__* irq_ptr; TYPE_3__ q_stats; int /*<<< orphan*/  nr_buf_used; TYPE_2__ u; int /*<<< orphan*/  timestamp; } ;
struct TYPE_9__ {int /*<<< orphan*/  perf_stat_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_4__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 scalar_t__ QDIO_IQDIO_QFMT ; 
#define  SLSB_CU_OUTPUT_PRIMED 133 
#define  SLSB_P_OUTPUT_EMPTY 132 
#define  SLSB_P_OUTPUT_ERROR 131 
#define  SLSB_P_OUTPUT_HALTED 130 
#define  SLSB_P_OUTPUT_NOT_INIT 129 
#define  SLSB_P_OUTPUT_PENDING 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  account_sbals (struct qdio_q*,int) ; 
 int /*<<< orphan*/  account_sbals_error (struct qdio_q*,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int get_buf_states (struct qdio_q*,unsigned int,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tod_clock_fast () ; 
 scalar_t__ multicast_outbound (struct qdio_q*) ; 
 scalar_t__ need_siga_sync (struct qdio_q*) ; 
 int /*<<< orphan*/  pci_out_supported (TYPE_4__*) ; 
 int /*<<< orphan*/  process_buffer_error (struct qdio_q*,unsigned int,int) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 
 scalar_t__ queue_type (struct qdio_q*) ; 

__attribute__((used)) static int get_outbound_buffer_frontier(struct qdio_q *q, unsigned int start)
{
	unsigned char state = 0;
	int count;

	q->timestamp = get_tod_clock_fast();

	if (need_siga_sync(q))
		if (((queue_type(q) != QDIO_IQDIO_QFMT) &&
		    !pci_out_supported(q->irq_ptr)) ||
		    (queue_type(q) == QDIO_IQDIO_QFMT &&
		    multicast_outbound(q)))
			qdio_siga_sync_q(q);

	count = atomic_read(&q->nr_buf_used);
	if (!count)
		return 0;

	count = get_buf_states(q, start, &state, count, 0, q->u.out.use_cq);
	if (!count)
		return 0;

	switch (state) {
	case SLSB_P_OUTPUT_EMPTY:
	case SLSB_P_OUTPUT_PENDING:
		/* the adapter got it */
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr,
			"out empty:%1d %02x", q->nr, count);

		atomic_sub(count, &q->nr_buf_used);
		if (q->irq_ptr->perf_stat_enabled)
			account_sbals(q, count);
		return count;
	case SLSB_P_OUTPUT_ERROR:
		process_buffer_error(q, start, count);
		atomic_sub(count, &q->nr_buf_used);
		if (q->irq_ptr->perf_stat_enabled)
			account_sbals_error(q, count);
		return count;
	case SLSB_CU_OUTPUT_PRIMED:
		/* the adapter has not fetched the output yet */
		if (q->irq_ptr->perf_stat_enabled)
			q->q_stats.nr_sbal_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "out primed:%1d",
			      q->nr);
		return 0;
	case SLSB_P_OUTPUT_NOT_INIT:
	case SLSB_P_OUTPUT_HALTED:
		return 0;
	default:
		WARN_ON_ONCE(1);
		return 0;
	}
}