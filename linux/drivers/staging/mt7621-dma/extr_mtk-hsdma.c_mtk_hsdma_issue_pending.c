#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct mtk_hsdma_chan {TYPE_2__ vchan; int /*<<< orphan*/  id; int /*<<< orphan*/  desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mtk_hsdam_engine {TYPE_1__ ddev; int /*<<< orphan*/  task; int /*<<< orphan*/  chan_issued; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gdma_next_desc (struct mtk_hsdma_chan*) ; 
 struct mtk_hsdam_engine* mtk_hsdma_chan_get_dev (struct mtk_hsdma_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct mtk_hsdma_chan* to_mtk_hsdma_chan (struct dma_chan*) ; 
 scalar_t__ vchan_issue_pending (TYPE_2__*) ; 

__attribute__((used)) static void mtk_hsdma_issue_pending(struct dma_chan *c)
{
	struct mtk_hsdma_chan *chan = to_mtk_hsdma_chan(c);
	struct mtk_hsdam_engine *hsdma = mtk_hsdma_chan_get_dev(chan);

	spin_lock_bh(&chan->vchan.lock);
	if (vchan_issue_pending(&chan->vchan) && !chan->desc) {
		if (gdma_next_desc(chan)) {
			set_bit(chan->id, &hsdma->chan_issued);
			tasklet_schedule(&hsdma->task);
		} else {
			dev_dbg(hsdma->ddev.dev, "no desc to issue\n");
		}
	}
	spin_unlock_bh(&chan->vchan.lock);
}