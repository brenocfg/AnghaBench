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
typedef  void uint8_t ;
struct r852_device {int dma_dir; int dma_stage; void* bounce_buffer; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  phys_bounce_buffer; int /*<<< orphan*/  phys_dma_addr; TYPE_1__* pci_dev; int /*<<< orphan*/  dma_state; int /*<<< orphan*/  dma_done; scalar_t__ dma_error; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_INTERNAL ; 
 int /*<<< orphan*/  DMA_MEMORY ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int R852_DMA_LEN ; 
 int /*<<< orphan*/  dbg_verbose (char*,...) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  r852_dma_done (struct r852_device*,int) ; 
 int /*<<< orphan*/  r852_dma_enable (struct r852_device*) ; 
 int r852_dma_wait (struct r852_device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void r852_do_dma(struct r852_device *dev, uint8_t *buf, int do_read)
{
	int bounce = 0;
	unsigned long flags;
	int error;

	dev->dma_error = 0;

	/* Set dma direction */
	dev->dma_dir = do_read;
	dev->dma_stage = 1;
	reinit_completion(&dev->dma_done);

	dbg_verbose("doing dma %s ", do_read ? "read" : "write");

	/* Set initial dma state: for reading first fill on board buffer,
	  from device, for writes first fill the buffer  from memory*/
	dev->dma_state = do_read ? DMA_INTERNAL : DMA_MEMORY;

	/* if incoming buffer is not page aligned, we should do bounce */
	if ((unsigned long)buf & (R852_DMA_LEN-1))
		bounce = 1;

	if (!bounce) {
		dev->phys_dma_addr = dma_map_single(&dev->pci_dev->dev, buf,
			R852_DMA_LEN,
			do_read ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
		if (dma_mapping_error(&dev->pci_dev->dev, dev->phys_dma_addr))
			bounce = 1;
	}

	if (bounce) {
		dbg_verbose("dma: using bounce buffer");
		dev->phys_dma_addr = dev->phys_bounce_buffer;
		if (!do_read)
			memcpy(dev->bounce_buffer, buf, R852_DMA_LEN);
	}

	/* Enable DMA */
	spin_lock_irqsave(&dev->irqlock, flags);
	r852_dma_enable(dev);
	spin_unlock_irqrestore(&dev->irqlock, flags);

	/* Wait till complete */
	error = r852_dma_wait(dev);

	if (error) {
		r852_dma_done(dev, error);
		return;
	}

	if (do_read && bounce)
		memcpy((void *)buf, dev->bounce_buffer, R852_DMA_LEN);
}