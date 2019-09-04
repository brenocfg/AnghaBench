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
struct pch_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  err_status; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdc_advance_work (struct pch_dma_chan*) ; 
 int /*<<< orphan*/  pdc_handle_error (struct pch_dma_chan*) ; 
 int /*<<< orphan*/  pdc_is_idle (struct pch_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdc_tasklet(unsigned long data)
{
	struct pch_dma_chan *pd_chan = (struct pch_dma_chan *)data;
	unsigned long flags;

	if (!pdc_is_idle(pd_chan)) {
		dev_err(chan2dev(&pd_chan->chan),
			"BUG: handle non-idle channel in tasklet\n");
		return;
	}

	spin_lock_irqsave(&pd_chan->lock, flags);
	if (test_and_clear_bit(0, &pd_chan->err_status))
		pdc_handle_error(pd_chan);
	else
		pdc_advance_work(pd_chan);
	spin_unlock_irqrestore(&pd_chan->lock, flags);
}