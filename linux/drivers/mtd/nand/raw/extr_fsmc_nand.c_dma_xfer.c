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
struct fsmc_nand_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_access_complete; int /*<<< orphan*/  data_pa; struct dma_chan* read_dma_chan; struct dma_chan* write_dma_chan; } ;
struct dma_device {int /*<<< orphan*/  dev; struct dma_async_tx_descriptor* (* device_prep_dma_memcpy ) (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ;} ;
struct dma_chan {struct dma_device* device; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;struct fsmc_nand_data* callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_CTRL_ACK ; 
 int DMA_FROM_DEVICE ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 int DMA_TO_DEVICE ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int /*<<< orphan*/  dma_complete ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int,int) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct dma_async_tx_descriptor* stub1 (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct dma_async_tx_descriptor*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_xfer(struct fsmc_nand_data *host, void *buffer, int len,
		    enum dma_data_direction direction)
{
	struct dma_chan *chan;
	struct dma_device *dma_dev;
	struct dma_async_tx_descriptor *tx;
	dma_addr_t dma_dst, dma_src, dma_addr;
	dma_cookie_t cookie;
	unsigned long flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	int ret;
	unsigned long time_left;

	if (direction == DMA_TO_DEVICE)
		chan = host->write_dma_chan;
	else if (direction == DMA_FROM_DEVICE)
		chan = host->read_dma_chan;
	else
		return -EINVAL;

	dma_dev = chan->device;
	dma_addr = dma_map_single(dma_dev->dev, buffer, len, direction);

	if (direction == DMA_TO_DEVICE) {
		dma_src = dma_addr;
		dma_dst = host->data_pa;
	} else {
		dma_src = host->data_pa;
		dma_dst = dma_addr;
	}

	tx = dma_dev->device_prep_dma_memcpy(chan, dma_dst, dma_src,
			len, flags);
	if (!tx) {
		dev_err(host->dev, "device_prep_dma_memcpy error\n");
		ret = -EIO;
		goto unmap_dma;
	}

	tx->callback = dma_complete;
	tx->callback_param = host;
	cookie = tx->tx_submit(tx);

	ret = dma_submit_error(cookie);
	if (ret) {
		dev_err(host->dev, "dma_submit_error %d\n", cookie);
		goto unmap_dma;
	}

	dma_async_issue_pending(chan);

	time_left =
	wait_for_completion_timeout(&host->dma_access_complete,
				    msecs_to_jiffies(3000));
	if (time_left == 0) {
		dmaengine_terminate_all(chan);
		dev_err(host->dev, "wait_for_completion_timeout\n");
		ret = -ETIMEDOUT;
		goto unmap_dma;
	}

	ret = 0;

unmap_dma:
	dma_unmap_single(dma_dev->dev, dma_addr, len, direction);

	return ret;
}