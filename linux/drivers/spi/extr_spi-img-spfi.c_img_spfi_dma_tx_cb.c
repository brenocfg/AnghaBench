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
struct img_spfi {int tx_dma_busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  master; int /*<<< orphan*/  rx_dma_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spfi_wait_all_done (struct img_spfi*) ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void img_spfi_dma_tx_cb(void *data)
{
	struct img_spfi *spfi = data;
	unsigned long flags;

	spfi_wait_all_done(spfi);

	spin_lock_irqsave(&spfi->lock, flags);
	spfi->tx_dma_busy = false;
	if (!spfi->rx_dma_busy)
		spi_finalize_current_transfer(spfi->master);
	spin_unlock_irqrestore(&spfi->lock, flags);
}