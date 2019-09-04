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
struct TYPE_6__ {int /*<<< orphan*/  instr_processed; } ;
struct octeon_instr_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  instr_pending; TYPE_3__ stats; int /*<<< orphan*/  host_write_index; int /*<<< orphan*/  octeon_read_index; scalar_t__ fill_cnt; } ;
struct TYPE_5__ {int iq; } ;
struct octeon_device {struct octeon_instr_queue** instr_queue; TYPE_2__ io_qmask; TYPE_1__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int MAX_OCTEON_INSTR_QUEUES (struct octeon_device*) ; 
 int /*<<< orphan*/  WAIT_INFLIGHT_REQUEST ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  force_io_queues_off (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_process_iq_request_list (struct octeon_device*,struct octeon_instr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_process_ordered_list (struct octeon_device*,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_pending_requests (struct octeon_device*) ; 

__attribute__((used)) static inline void pcierror_quiesce_device(struct octeon_device *oct)
{
	int i;

	/* Disable the input and output queues now. No more packets will
	 * arrive from Octeon, but we should wait for all packet processing
	 * to finish.
	 */
	force_io_queues_off(oct);

	/* To allow for in-flight requests */
	schedule_timeout_uninterruptible(WAIT_INFLIGHT_REQUEST);

	if (wait_for_pending_requests(oct))
		dev_err(&oct->pci_dev->dev, "There were pending requests\n");

	/* Force all requests waiting to be fetched by OCTEON to complete. */
	for (i = 0; i < MAX_OCTEON_INSTR_QUEUES(oct); i++) {
		struct octeon_instr_queue *iq;

		if (!(oct->io_qmask.iq & BIT_ULL(i)))
			continue;
		iq = oct->instr_queue[i];

		if (atomic_read(&iq->instr_pending)) {
			spin_lock_bh(&iq->lock);
			iq->fill_cnt = 0;
			iq->octeon_read_index = iq->host_write_index;
			iq->stats.instr_processed +=
				atomic_read(&iq->instr_pending);
			lio_process_iq_request_list(oct, iq, 0);
			spin_unlock_bh(&iq->lock);
		}
	}

	/* Force all pending ordered list requests to time out. */
	lio_process_ordered_list(oct, 1);

	/* We do not need to wait for output queue packets to be processed. */
}