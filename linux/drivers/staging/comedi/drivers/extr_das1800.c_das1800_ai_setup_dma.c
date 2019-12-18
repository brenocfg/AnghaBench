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
struct das1800_private {int irq_dma_bits; struct comedi_isadma* dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_isadma_desc {unsigned int size; int /*<<< orphan*/  maxsize; } ;
struct comedi_isadma {struct comedi_isadma_desc* desc; scalar_t__ cur_dma; } ;
struct comedi_device {struct das1800_private* private; } ;

/* Variables and functions */
 int DMA_DUAL ; 
 int DMA_ENABLED ; 
 int /*<<< orphan*/  comedi_isadma_program (struct comedi_isadma_desc*) ; 
 unsigned int das1800_ai_transfer_size (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void das1800_ai_setup_dma(struct comedi_device *dev,
				 struct comedi_subdevice *s)
{
	struct das1800_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc;
	unsigned int bytes;

	if ((devpriv->irq_dma_bits & DMA_ENABLED) == 0)
		return;

	dma->cur_dma = 0;
	desc = &dma->desc[0];

	/* determine a dma transfer size to fill buffer in 0.3 sec */
	bytes = das1800_ai_transfer_size(dev, s, desc->maxsize, 300000000);

	desc->size = bytes;
	comedi_isadma_program(desc);

	/* set up dual dma if appropriate */
	if (devpriv->irq_dma_bits & DMA_DUAL) {
		desc = &dma->desc[1];
		desc->size = bytes;
		comedi_isadma_program(desc);
	}
}