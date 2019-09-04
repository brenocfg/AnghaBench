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
struct msgdma_device {int idle; scalar_t__ csr; int /*<<< orphan*/  irq_tasklet; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MSGDMA_CSR_STATUS ; 
 int MSGDMA_CSR_STAT_BUSY ; 
 int /*<<< orphan*/  MSGDMA_CSR_STAT_IRQ ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msgdma_start_transfer (struct msgdma_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t msgdma_irq_handler(int irq, void *data)
{
	struct msgdma_device *mdev = data;
	u32 status;

	status = ioread32(mdev->csr + MSGDMA_CSR_STATUS);
	if ((status & MSGDMA_CSR_STAT_BUSY) == 0) {
		/* Start next transfer if the DMA controller is idle */
		spin_lock(&mdev->lock);
		mdev->idle = true;
		msgdma_start_transfer(mdev);
		spin_unlock(&mdev->lock);
	}

	tasklet_schedule(&mdev->irq_tasklet);

	/* Clear interrupt in mSGDMA controller */
	iowrite32(MSGDMA_CSR_STAT_IRQ, mdev->csr + MSGDMA_CSR_STATUS);

	return IRQ_HANDLED;
}