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
typedef  scalar_t__ u16 ;
struct hl_hw_queue {int /*<<< orphan*/  ci; struct hl_cs_job** shadow_queue; } ;
struct hl_device {int /*<<< orphan*/  cq_wq; scalar_t__ disabled; struct hl_hw_queue* kernel_queues; int /*<<< orphan*/  dev; } ;
struct hl_cs_job {int /*<<< orphan*/  finish_work; } ;
struct hl_cq_entry {int /*<<< orphan*/  data; } ;
struct hl_cq {size_t hw_queue_id; size_t ci; int /*<<< orphan*/  free_slots_cnt; scalar_t__ kernel_address; struct hl_device* hdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CQ_ENTRY_READY_MASK ; 
 int CQ_ENTRY_READY_SHIFT ; 
 int CQ_ENTRY_SHADOW_INDEX_MASK ; 
 int CQ_ENTRY_SHADOW_INDEX_SHIFT ; 
 int CQ_ENTRY_SHADOW_INDEX_VALID_MASK ; 
 int CQ_ENTRY_SHADOW_INDEX_VALID_SHIFT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 size_t hl_cq_inc_ptr (size_t) ; 
 size_t hl_pi_2_offset (scalar_t__) ; 
 int /*<<< orphan*/  hl_queue_inc_ptr (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t hl_irq_handler_cq(int irq, void *arg)
{
	struct hl_cq *cq = arg;
	struct hl_device *hdev = cq->hdev;
	struct hl_hw_queue *queue;
	struct hl_cs_job *job;
	bool shadow_index_valid;
	u16 shadow_index;
	struct hl_cq_entry *cq_entry, *cq_base;

	if (hdev->disabled) {
		dev_dbg(hdev->dev,
			"Device disabled but received IRQ %d for CQ %d\n",
			irq, cq->hw_queue_id);
		return IRQ_HANDLED;
	}

	cq_base = (struct hl_cq_entry *) (uintptr_t) cq->kernel_address;

	while (1) {
		bool entry_ready = ((le32_to_cpu(cq_base[cq->ci].data) &
					CQ_ENTRY_READY_MASK)
						>> CQ_ENTRY_READY_SHIFT);

		if (!entry_ready)
			break;

		cq_entry = (struct hl_cq_entry *) &cq_base[cq->ci];

		/* Make sure we read CQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		shadow_index_valid = ((le32_to_cpu(cq_entry->data) &
					CQ_ENTRY_SHADOW_INDEX_VALID_MASK)
					>> CQ_ENTRY_SHADOW_INDEX_VALID_SHIFT);

		shadow_index = (u16) ((le32_to_cpu(cq_entry->data) &
					CQ_ENTRY_SHADOW_INDEX_MASK)
					>> CQ_ENTRY_SHADOW_INDEX_SHIFT);

		queue = &hdev->kernel_queues[cq->hw_queue_id];

		if ((shadow_index_valid) && (!hdev->disabled)) {
			job = queue->shadow_queue[hl_pi_2_offset(shadow_index)];
			queue_work(hdev->cq_wq, &job->finish_work);
		}

		/* Update ci of the context's queue. There is no
		 * need to protect it with spinlock because this update is
		 * done only inside IRQ and there is a different IRQ per
		 * queue
		 */
		queue->ci = hl_queue_inc_ptr(queue->ci);

		/* Clear CQ entry ready bit */
		cq_entry->data = cpu_to_le32(le32_to_cpu(cq_entry->data) &
						~CQ_ENTRY_READY_MASK);

		cq->ci = hl_cq_inc_ptr(cq->ci);

		/* Increment free slots */
		atomic_inc(&cq->free_slots_cnt);
	}

	return IRQ_HANDLED;
}