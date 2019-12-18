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
struct dt282x_private {int /*<<< orphan*/  dma; } ;
struct comedi_device {unsigned int irq; int /*<<< orphan*/  board_name; struct dt282x_private* private; } ;
struct comedi_devconfig {unsigned int* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  comedi_isadma_alloc (struct comedi_device*,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt282x_interrupt ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct comedi_device*) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static void dt282x_alloc_dma(struct comedi_device *dev,
			     struct comedi_devconfig *it)
{
	struct dt282x_private *devpriv = dev->private;
	unsigned int irq_num = it->options[1];
	unsigned int dma_chan[2];

	if (it->options[2] < it->options[3]) {
		dma_chan[0] = it->options[2];
		dma_chan[1] = it->options[3];
	} else {
		dma_chan[0] = it->options[3];
		dma_chan[1] = it->options[2];
	}

	if (!irq_num || dma_chan[0] == dma_chan[1] ||
	    dma_chan[0] < 5 || dma_chan[0] > 7 ||
	    dma_chan[1] < 5 || dma_chan[1] > 7)
		return;

	if (request_irq(irq_num, dt282x_interrupt, 0, dev->board_name, dev))
		return;

	/* DMA uses two 4K buffers with separate DMA channels */
	devpriv->dma = comedi_isadma_alloc(dev, 2, dma_chan[0], dma_chan[1],
					   PAGE_SIZE, 0);
	if (!devpriv->dma)
		free_irq(irq_num, dev);
	else
		dev->irq = irq_num;
}