#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct r592_device {int dma_error; TYPE_2__* req; TYPE_1__* pci_dev; int /*<<< orphan*/  dma_done; int /*<<< orphan*/  dma_capable; } ;
struct TYPE_8__ {int length; } ;
struct TYPE_7__ {scalar_t__ data_dir; TYPE_3__ sg; int /*<<< orphan*/  long_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int R592_LFIFO_SIZE ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 int dma_map_sg (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message (char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  r592_start_dma (struct r592_device*,int) ; 
 int /*<<< orphan*/  r592_stop_dma (struct r592_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int sg_dma_len (TYPE_3__*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r592_transfer_fifo_dma(struct r592_device *dev)
{
	int len, sg_count;
	bool is_write;

	if (!dev->dma_capable || !dev->req->long_data)
		return -EINVAL;

	len = dev->req->sg.length;
	is_write = dev->req->data_dir == WRITE;

	if (len != R592_LFIFO_SIZE)
		return -EINVAL;

	dbg_verbose("doing dma transfer");

	dev->dma_error = 0;
	reinit_completion(&dev->dma_done);

	/* TODO: hidden assumption about nenth beeing always 1 */
	sg_count = dma_map_sg(&dev->pci_dev->dev, &dev->req->sg, 1, is_write ?
		PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);

	if (sg_count != 1 || sg_dma_len(&dev->req->sg) < R592_LFIFO_SIZE) {
		message("problem in dma_map_sg");
		return -EIO;
	}

	r592_start_dma(dev, is_write);

	/* Wait for DMA completion */
	if (!wait_for_completion_timeout(
			&dev->dma_done, msecs_to_jiffies(1000))) {
		message("DMA timeout");
		r592_stop_dma(dev, -ETIMEDOUT);
	}

	dma_unmap_sg(&dev->pci_dev->dev, &dev->req->sg, 1, is_write ?
		PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);


	return dev->dma_error;
}