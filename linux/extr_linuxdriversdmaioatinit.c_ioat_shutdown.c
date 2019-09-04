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
struct pci_dev {int dummy; } ;
struct ioatdma_device {struct ioatdma_chan** idx; } ;
struct ioatdma_chan {int /*<<< orphan*/  timer; int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHAN_DOWN ; 
 int IOAT_MAX_CHANS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioat_disable_interrupts (struct ioatdma_device*) ; 
 int /*<<< orphan*/  ioat_reset_hw (struct ioatdma_chan*) ; 
 struct ioatdma_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ioat_shutdown(struct pci_dev *pdev)
{
	struct ioatdma_device *ioat_dma = pci_get_drvdata(pdev);
	struct ioatdma_chan *ioat_chan;
	int i;

	if (!ioat_dma)
		return;

	for (i = 0; i < IOAT_MAX_CHANS; i++) {
		ioat_chan = ioat_dma->idx[i];
		if (!ioat_chan)
			continue;

		spin_lock_bh(&ioat_chan->prep_lock);
		set_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
		spin_unlock_bh(&ioat_chan->prep_lock);
		/*
		 * Synchronization rule for del_timer_sync():
		 *  - The caller must not hold locks which would prevent
		 *    completion of the timer's handler.
		 * So prep_lock cannot be held before calling it.
		 */
		del_timer_sync(&ioat_chan->timer);

		/* this should quiesce then reset */
		ioat_reset_hw(ioat_chan);
	}

	ioat_disable_interrupts(ioat_dma);
}