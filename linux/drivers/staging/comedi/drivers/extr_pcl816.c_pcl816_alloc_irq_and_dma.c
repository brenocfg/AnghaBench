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
struct pcl816_private {int /*<<< orphan*/  dma; } ;
struct comedi_device {unsigned int irq; int /*<<< orphan*/  board_name; struct pcl816_private* private; } ;
struct comedi_devconfig {unsigned int* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_ISADMA_READ ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  comedi_isadma_alloc (struct comedi_device*,int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct comedi_device*) ; 
 int /*<<< orphan*/  pcl816_interrupt ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static void pcl816_alloc_irq_and_dma(struct comedi_device *dev,
				     struct comedi_devconfig *it)
{
	struct pcl816_private *devpriv = dev->private;
	unsigned int irq_num = it->options[1];
	unsigned int dma_chan = it->options[2];

	/* only IRQs 2-7 and DMA channels 3 and 1 are valid */
	if (!(irq_num >= 2 && irq_num <= 7) ||
	    !(dma_chan == 3 || dma_chan == 1))
		return;

	if (request_irq(irq_num, pcl816_interrupt, 0, dev->board_name, dev))
		return;

	/* DMA uses two 16K buffers */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 4, COMEDI_ISADMA_READ);
	if (!devpriv->dma)
		free_irq(irq_num, dev);
	else
		dev->irq = irq_num;
}