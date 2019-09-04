#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct st_fdma_chan {TYPE_1__ vchan; int /*<<< orphan*/  fdesc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  st_fdma_xfer_desc (struct st_fdma_chan*) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_1__*) ; 

__attribute__((used)) static void st_fdma_issue_pending(struct dma_chan *chan)
{
	struct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&fchan->vchan.lock, flags);

	if (vchan_issue_pending(&fchan->vchan) && !fchan->fdesc)
		st_fdma_xfer_desc(fchan);

	spin_unlock_irqrestore(&fchan->vchan.lock, flags);
}