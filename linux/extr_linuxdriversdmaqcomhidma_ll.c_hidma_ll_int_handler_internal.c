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
struct hidma_lldev {int /*<<< orphan*/  lock; scalar_t__ evca; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HIDMA_ERR_INT_MASK ; 
 scalar_t__ HIDMA_EVCA_IRQ_CLR_REG ; 
 int /*<<< orphan*/  HIDMA_EVRE_STATUS_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hidma_cleanup_pending_tre (struct hidma_lldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidma_handle_tre_completion (struct hidma_lldev*) ; 
 int /*<<< orphan*/  hidma_ll_disable (struct hidma_lldev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void hidma_ll_int_handler_internal(struct hidma_lldev *lldev, int cause)
{
	unsigned long irqflags;

	if (cause & HIDMA_ERR_INT_MASK) {
		dev_err(lldev->dev, "error 0x%x, disabling...\n",
				cause);

		/* Clear out pending interrupts */
		writel(cause, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);

		/* No further submissions. */
		hidma_ll_disable(lldev);

		/* Driver completes the txn and intimates the client.*/
		hidma_cleanup_pending_tre(lldev, 0xFF,
					  HIDMA_EVRE_STATUS_ERROR);

		return;
	}

	spin_lock_irqsave(&lldev->lock, irqflags);
	writel_relaxed(cause, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	spin_unlock_irqrestore(&lldev->lock, irqflags);

	/*
	 * Fine tuned for this HW...
	 *
	 * This ISR has been designed for this particular hardware. Relaxed
	 * read and write accessors are used for performance reasons due to
	 * interrupt delivery guarantees. Do not copy this code blindly and
	 * expect that to work.
	 *
	 * Try to consume as many EVREs as possible.
	 */
	hidma_handle_tre_completion(lldev);
}