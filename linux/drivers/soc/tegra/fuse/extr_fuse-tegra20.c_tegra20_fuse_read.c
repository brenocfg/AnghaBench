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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ src_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * virt; int /*<<< orphan*/  chan; int /*<<< orphan*/  wait; int /*<<< orphan*/  phys; TYPE_2__ config; } ;
struct tegra_fuse {TYPE_1__ apbdma; int /*<<< orphan*/  clk; scalar_t__ phys; } ;
struct dma_async_tx_descriptor {struct tegra_fuse* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 unsigned long DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 scalar_t__ FUSE_BEGIN ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  apb_dma_complete ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 tegra20_fuse_read(struct tegra_fuse *fuse, unsigned int offset)
{
	unsigned long flags = DMA_PREP_INTERRUPT | DMA_CTRL_ACK;
	struct dma_async_tx_descriptor *dma_desc;
	unsigned long time_left;
	u32 value = 0;
	int err;

	mutex_lock(&fuse->apbdma.lock);

	fuse->apbdma.config.src_addr = fuse->phys + FUSE_BEGIN + offset;

	err = dmaengine_slave_config(fuse->apbdma.chan, &fuse->apbdma.config);
	if (err)
		goto out;

	dma_desc = dmaengine_prep_slave_single(fuse->apbdma.chan,
					       fuse->apbdma.phys,
					       sizeof(u32), DMA_DEV_TO_MEM,
					       flags);
	if (!dma_desc)
		goto out;

	dma_desc->callback = apb_dma_complete;
	dma_desc->callback_param = fuse;

	reinit_completion(&fuse->apbdma.wait);

	clk_prepare_enable(fuse->clk);

	dmaengine_submit(dma_desc);
	dma_async_issue_pending(fuse->apbdma.chan);
	time_left = wait_for_completion_timeout(&fuse->apbdma.wait,
						msecs_to_jiffies(50));

	if (WARN(time_left == 0, "apb read dma timed out"))
		dmaengine_terminate_all(fuse->apbdma.chan);
	else
		value = *fuse->apbdma.virt;

	clk_disable_unprepare(fuse->clk);

out:
	mutex_unlock(&fuse->apbdma.lock);
	return value;
}