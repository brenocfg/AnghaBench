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
struct ni_private {int /*<<< orphan*/  mite_channel_lock; struct mite_channel* cdo_mite_chan; int /*<<< orphan*/  cdo_mite_ring; int /*<<< orphan*/  mite; } ;
struct mite_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  dir; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_OUTPUT ; 
 int EBUSY ; 
 int /*<<< orphan*/  NI_M_CDIO_DMA_SEL_CDO (unsigned int) ; 
 int /*<<< orphan*/  NI_M_CDIO_DMA_SEL_CDO_MASK ; 
 int /*<<< orphan*/  NI_M_CDIO_DMA_SEL_REG ; 
 unsigned int NI_STC_DMA_CHAN_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mite_channel* mite_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_request_cdo_mite_channel(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	struct mite_channel *mite_chan;
	unsigned long flags;
	unsigned int bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite, devpriv->cdo_mite_ring);
	if (!mite_chan) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for correlated digital output\n");
		return -EBUSY;
	}
	mite_chan->dir = COMEDI_OUTPUT;
	devpriv->cdo_mite_chan = mite_chan;

	/*
	 * XXX just guessing NI_STC_DMA_CHAN_SEL()
	 * returns the right bits, under the assumption the cdio dma
	 * selection works just like ai/ao/gpct.
	 * Definitely works for dma channels 0 and 1.
	 */
	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_M_CDIO_DMA_SEL_REG,
			NI_M_CDIO_DMA_SEL_CDO_MASK,
			NI_M_CDIO_DMA_SEL_CDO(bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}