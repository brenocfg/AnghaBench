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
struct comedi_isadma_desc {unsigned int chan; unsigned int maxsize; int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  hw_addr; } ;
struct comedi_isadma {int n_desc; unsigned int chan; unsigned int chan2; scalar_t__ dev; struct comedi_isadma_desc* desc; } ;
struct comedi_device {int /*<<< orphan*/  board_name; scalar_t__ class_dev; scalar_t__ hw_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  comedi_isadma_free (struct comedi_isadma*) ; 
 int /*<<< orphan*/  comedi_isadma_set_mode (struct comedi_isadma_desc*,char) ; 
 int /*<<< orphan*/  dma_alloc_coherent (scalar_t__,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_coerce_mask_and_coherent (scalar_t__,int /*<<< orphan*/ ) ; 
 struct comedi_isadma_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct comedi_isadma* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_dma (unsigned int,int /*<<< orphan*/ ) ; 

struct comedi_isadma *comedi_isadma_alloc(struct comedi_device *dev,
					  int n_desc, unsigned int dma_chan1,
					  unsigned int dma_chan2,
					  unsigned int maxsize, char dma_dir)
{
	struct comedi_isadma *dma = NULL;
	struct comedi_isadma_desc *desc;
	unsigned int dma_chans[2];
	int i;

	if (n_desc < 1 || n_desc > 2)
		goto no_dma;

	dma = kzalloc(sizeof(*dma), GFP_KERNEL);
	if (!dma)
		goto no_dma;

	desc = kcalloc(n_desc, sizeof(*desc), GFP_KERNEL);
	if (!desc)
		goto no_dma;
	dma->desc = desc;
	dma->n_desc = n_desc;
	if (dev->hw_dev) {
		dma->dev = dev->hw_dev;
	} else {
		/* Fall back to using the "class" device. */
		if (!dev->class_dev)
			goto no_dma;
		/* Need 24-bit mask for ISA DMA. */
		if (dma_coerce_mask_and_coherent(dev->class_dev,
						 DMA_BIT_MASK(24))) {
			goto no_dma;
		}
		dma->dev = dev->class_dev;
	}

	dma_chans[0] = dma_chan1;
	if (dma_chan2 == 0 || dma_chan2 == dma_chan1)
		dma_chans[1] = dma_chan1;
	else
		dma_chans[1] = dma_chan2;

	if (request_dma(dma_chans[0], dev->board_name))
		goto no_dma;
	dma->chan = dma_chans[0];
	if (dma_chans[1] != dma_chans[0]) {
		if (request_dma(dma_chans[1], dev->board_name))
			goto no_dma;
	}
	dma->chan2 = dma_chans[1];

	for (i = 0; i < n_desc; i++) {
		desc = &dma->desc[i];
		desc->chan = dma_chans[i];
		desc->maxsize = maxsize;
		desc->virt_addr = dma_alloc_coherent(dma->dev, desc->maxsize,
						     &desc->hw_addr,
						     GFP_KERNEL);
		if (!desc->virt_addr)
			goto no_dma;
		comedi_isadma_set_mode(desc, dma_dir);
	}

	return dma;

no_dma:
	comedi_isadma_free(dma);
	return NULL;
}