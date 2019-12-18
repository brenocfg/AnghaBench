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
typedef  int /*<<< orphan*/  uint32_t ;
struct sh_flctl {TYPE_1__* pdev; int /*<<< orphan*/  dma_complete; struct dma_chan* chan_fifo0_tx; struct dma_chan* chan_fifo0_rx; } ;
struct dma_chan {TYPE_2__* device; } ;
struct dma_async_tx_descriptor {struct sh_flctl* callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_FROM_DEVICE ; 
 int DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DREQ0EN ; 
 int EIO ; 
 int /*<<< orphan*/  FLINTDMACR (struct sh_flctl*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,unsigned long*,int,int) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (struct dma_chan*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  flctl_dma_complete ; 
 int /*<<< orphan*/  flctl_release_dma (struct sh_flctl*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flctl_dma_fifo0_transfer(struct sh_flctl *flctl, unsigned long *buf,
					int len, enum dma_data_direction dir)
{
	struct dma_async_tx_descriptor *desc = NULL;
	struct dma_chan *chan;
	enum dma_transfer_direction tr_dir;
	dma_addr_t dma_addr;
	dma_cookie_t cookie;
	uint32_t reg;
	int ret;

	if (dir == DMA_FROM_DEVICE) {
		chan = flctl->chan_fifo0_rx;
		tr_dir = DMA_DEV_TO_MEM;
	} else {
		chan = flctl->chan_fifo0_tx;
		tr_dir = DMA_MEM_TO_DEV;
	}

	dma_addr = dma_map_single(chan->device->dev, buf, len, dir);

	if (!dma_mapping_error(chan->device->dev, dma_addr))
		desc = dmaengine_prep_slave_single(chan, dma_addr, len,
			tr_dir, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	if (desc) {
		reg = readl(FLINTDMACR(flctl));
		reg |= DREQ0EN;
		writel(reg, FLINTDMACR(flctl));

		desc->callback = flctl_dma_complete;
		desc->callback_param = flctl;
		cookie = dmaengine_submit(desc);
		if (dma_submit_error(cookie)) {
			ret = dma_submit_error(cookie);
			dev_warn(&flctl->pdev->dev,
				 "DMA submit failed, falling back to PIO\n");
			goto out;
		}

		dma_async_issue_pending(chan);
	} else {
		/* DMA failed, fall back to PIO */
		flctl_release_dma(flctl);
		dev_warn(&flctl->pdev->dev,
			 "DMA failed, falling back to PIO\n");
		ret = -EIO;
		goto out;
	}

	ret =
	wait_for_completion_timeout(&flctl->dma_complete,
				msecs_to_jiffies(3000));

	if (ret <= 0) {
		dmaengine_terminate_all(chan);
		dev_err(&flctl->pdev->dev, "wait_for_completion_timeout\n");
	}

out:
	reg = readl(FLINTDMACR(flctl));
	reg &= ~DREQ0EN;
	writel(reg, FLINTDMACR(flctl));

	dma_unmap_single(chan->device->dev, dma_addr, len, dir);

	/* ret > 0 is success */
	return ret;
}