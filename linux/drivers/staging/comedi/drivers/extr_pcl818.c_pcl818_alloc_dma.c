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
struct pcl818_private {int /*<<< orphan*/  dma; } ;
struct comedi_device {struct pcl818_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_ISADMA_READ ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  comedi_isadma_alloc (struct comedi_device*,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcl818_alloc_dma(struct comedi_device *dev, unsigned int dma_chan)
{
	struct pcl818_private *devpriv = dev->private;

	/* only DMA channels 3 and 1 are valid */
	if (!(dma_chan == 3 || dma_chan == 1))
		return;

	/* DMA uses two 16K buffers */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 4, COMEDI_ISADMA_READ);
}