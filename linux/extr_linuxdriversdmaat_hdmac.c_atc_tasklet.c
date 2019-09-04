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
struct at_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATC_IS_ERROR ; 
 int /*<<< orphan*/  atc_advance_work (struct at_dma_chan*) ; 
 scalar_t__ atc_chan_is_cyclic (struct at_dma_chan*) ; 
 int /*<<< orphan*/  atc_handle_cyclic (struct at_dma_chan*) ; 
 int /*<<< orphan*/  atc_handle_error (struct at_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atc_tasklet(unsigned long data)
{
	struct at_dma_chan *atchan = (struct at_dma_chan *)data;
	unsigned long flags;

	spin_lock_irqsave(&atchan->lock, flags);
	if (test_and_clear_bit(ATC_IS_ERROR, &atchan->status))
		atc_handle_error(atchan);
	else if (atc_chan_is_cyclic(atchan))
		atc_handle_cyclic(atchan);
	else
		atc_advance_work(atchan);

	spin_unlock_irqrestore(&atchan->lock, flags);
}