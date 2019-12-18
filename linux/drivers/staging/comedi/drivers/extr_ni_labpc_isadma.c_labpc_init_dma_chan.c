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
struct labpc_private {int /*<<< orphan*/  dma; } ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_ISADMA_READ ; 
 int /*<<< orphan*/  LABPC_ISADMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  comedi_isadma_alloc (struct comedi_device*,int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void labpc_init_dma_chan(struct comedi_device *dev, unsigned int dma_chan)
{
	struct labpc_private *devpriv = dev->private;

	/* only DMA channels 3 and 1 are valid */
	if (dma_chan != 1 && dma_chan != 3)
		return;

	/* DMA uses 1 buffer */
	devpriv->dma = comedi_isadma_alloc(dev, 1, dma_chan, dma_chan,
					   LABPC_ISADMA_BUFFER_SIZE,
					   COMEDI_ISADMA_READ);
}