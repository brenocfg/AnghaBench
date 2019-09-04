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
struct shdma_chan {scalar_t__ pm_state; int /*<<< orphan*/  chan_lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ SHDMA_PM_ESTABLISHED ; 
 scalar_t__ SHDMA_PM_PENDING ; 
 int /*<<< orphan*/  shdma_chan_xfer_ld_queue (struct shdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct shdma_chan* to_shdma_chan (struct dma_chan*) ; 

__attribute__((used)) static void shdma_issue_pending(struct dma_chan *chan)
{
	struct shdma_chan *schan = to_shdma_chan(chan);

	spin_lock_irq(&schan->chan_lock);
	if (schan->pm_state == SHDMA_PM_ESTABLISHED)
		shdma_chan_xfer_ld_queue(schan);
	else
		schan->pm_state = SHDMA_PM_PENDING;
	spin_unlock_irq(&schan->chan_lock);
}