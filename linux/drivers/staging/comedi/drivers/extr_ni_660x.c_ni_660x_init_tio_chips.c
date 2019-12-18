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
struct ni_660x_private {int /*<<< orphan*/ * dma_cfg; } ;
struct comedi_device {struct ni_660x_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI660X_DMA_CFG ; 
 int /*<<< orphan*/  NI660X_DMA_CFG_SEL_NONE (unsigned int) ; 
 int /*<<< orphan*/  NI660X_IO_CFG (unsigned int) ; 
 unsigned int NI660X_MAX_DMA_CHANNEL ; 
 unsigned int NI660X_NUM_PFI_CHANNELS ; 
 int /*<<< orphan*/  NI660X_STC_DIO_CONTROL ; 
 int /*<<< orphan*/  ni_660x_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_660x_init_tio_chips(struct comedi_device *dev,
				   unsigned int n_chips)
{
	struct ni_660x_private *devpriv = dev->private;
	unsigned int chip;
	unsigned int chan;

	/*
	 * We use the ioconfig registers to control dio direction, so zero
	 * output enables in stc dio control reg.
	 */
	ni_660x_write(dev, 0, 0, NI660X_STC_DIO_CONTROL);

	for (chip = 0; chip < n_chips; ++chip) {
		/* init dma configuration register */
		devpriv->dma_cfg[chip] = 0;
		for (chan = 0; chan < NI660X_MAX_DMA_CHANNEL; ++chan)
			devpriv->dma_cfg[chip] |= NI660X_DMA_CFG_SEL_NONE(chan);
		ni_660x_write(dev, chip, devpriv->dma_cfg[chip],
			      NI660X_DMA_CFG);

		/* init ioconfig registers */
		for (chan = 0; chan < NI660X_NUM_PFI_CHANNELS; ++chan)
			ni_660x_write(dev, chip, 0, NI660X_IO_CFG(chan));
	}
}