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
typedef  int u32 ;
struct rx_ring {int /*<<< orphan*/  napi; struct ql_adapter* qdev; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  mpi_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  hw_lock; struct intr_context* intr_context; } ;
struct intr_context {int irq_mask; int /*<<< orphan*/  intr; int /*<<< orphan*/  irq_cnt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_STS ; 
 int /*<<< orphan*/  INTR_MASK ; 
 int INTR_MASK_PI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR1 ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int STS_FE ; 
 int STS_PI ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_info (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_disable_completion_interrupt (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_enable_completion_interrupt (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_queue_asic_error (struct ql_adapter*) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t qlge_isr(int irq, void *dev_id)
{
	struct rx_ring *rx_ring = dev_id;
	struct ql_adapter *qdev = rx_ring->qdev;
	struct intr_context *intr_context = &qdev->intr_context[0];
	u32 var;
	int work_done = 0;

	spin_lock(&qdev->hw_lock);
	if (atomic_read(&qdev->intr_context[0].irq_cnt)) {
		netif_printk(qdev, intr, KERN_DEBUG, qdev->ndev,
			     "Shared Interrupt, Not ours!\n");
		spin_unlock(&qdev->hw_lock);
		return IRQ_NONE;
	}
	spin_unlock(&qdev->hw_lock);

	var = ql_disable_completion_interrupt(qdev, intr_context->intr);

	/*
	 * Check for fatal error.
	 */
	if (var & STS_FE) {
		ql_queue_asic_error(qdev);
		netdev_err(qdev->ndev, "Got fatal error, STS = %x.\n", var);
		var = ql_read32(qdev, ERR_STS);
		netdev_err(qdev->ndev, "Resetting chip. "
					"Error Status Register = 0x%x\n", var);
		return IRQ_HANDLED;
	}

	/*
	 * Check MPI processor activity.
	 */
	if ((var & STS_PI) &&
		(ql_read32(qdev, INTR_MASK) & INTR_MASK_PI)) {
		/*
		 * We've got an async event or mailbox completion.
		 * Handle it and clear the source of the interrupt.
		 */
		netif_err(qdev, intr, qdev->ndev,
			  "Got MPI processor interrupt.\n");
		ql_disable_completion_interrupt(qdev, intr_context->intr);
		ql_write32(qdev, INTR_MASK, (INTR_MASK_PI << 16));
		queue_delayed_work_on(smp_processor_id(),
				qdev->workqueue, &qdev->mpi_work, 0);
		work_done++;
	}

	/*
	 * Get the bit-mask that shows the active queues for this
	 * pass.  Compare it to the queues that this irq services
	 * and call napi if there's a match.
	 */
	var = ql_read32(qdev, ISR1);
	if (var & intr_context->irq_mask) {
		netif_info(qdev, intr, qdev->ndev,
			   "Waking handler for rx_ring[0].\n");
		ql_disable_completion_interrupt(qdev, intr_context->intr);
		napi_schedule(&rx_ring->napi);
		work_done++;
	}
	ql_enable_completion_interrupt(qdev, intr_context->intr);
	return work_done ? IRQ_HANDLED : IRQ_NONE;
}