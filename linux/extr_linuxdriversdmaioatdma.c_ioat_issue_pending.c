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
struct ioatdma_chan {int /*<<< orphan*/  prep_lock; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ioat_issue_pending (struct ioatdma_chan*) ; 
 scalar_t__ ioat_ring_pending (struct ioatdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 

void ioat_issue_pending(struct dma_chan *c)
{
	struct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	if (ioat_ring_pending(ioat_chan)) {
		spin_lock_bh(&ioat_chan->prep_lock);
		__ioat_issue_pending(ioat_chan);
		spin_unlock_bh(&ioat_chan->prep_lock);
	}
}