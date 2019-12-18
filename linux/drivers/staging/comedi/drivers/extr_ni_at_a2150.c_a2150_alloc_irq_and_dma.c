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
struct comedi_device {unsigned int irq; int /*<<< orphan*/  board_name; struct a2150_private* private; } ;
struct comedi_devconfig {unsigned int* options; } ;
struct a2150_private {int irq_dma_bits; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2150_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  COMEDI_ISADMA_READ ; 
 int DMA_CHAN_BITS (unsigned int) ; 
 int IRQ_LVL_BITS (unsigned int) ; 
 int /*<<< orphan*/  a2150_interrupt ; 
 int /*<<< orphan*/  comedi_isadma_alloc (struct comedi_device*,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct comedi_device*) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 

__attribute__((used)) static void a2150_alloc_irq_and_dma(struct comedi_device *dev,
				    struct comedi_devconfig *it)
{
	struct a2150_private *devpriv = dev->private;
	unsigned int irq_num = it->options[1];
	unsigned int dma_chan = it->options[2];

	/*
	 * Only IRQs 15, 14, 12-9, and 7-3 are valid.
	 * Only DMA channels 7-5 and 3-0 are valid.
	 */
	if (irq_num > 15 || dma_chan > 7 ||
	    !((1 << irq_num) & 0xdef8) || !((1 << dma_chan) & 0xef))
		return;

	if (request_irq(irq_num, a2150_interrupt, 0, dev->board_name, dev))
		return;

	/* DMA uses 1 buffer */
	devpriv->dma = comedi_isadma_alloc(dev, 1, dma_chan, dma_chan,
					   A2150_DMA_BUFFER_SIZE,
					   COMEDI_ISADMA_READ);
	if (!devpriv->dma) {
		free_irq(irq_num, dev);
	} else {
		dev->irq = irq_num;
		devpriv->irq_dma_bits = IRQ_LVL_BITS(irq_num) |
					DMA_CHAN_BITS(dma_chan);
	}
}