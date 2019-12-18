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
struct ni_private {int /*<<< orphan*/  mite_channel_lock; struct mite_channel* ai_mite_chan; int /*<<< orphan*/  ai_mite_ring; int /*<<< orphan*/  mite; } ;
struct mite_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  dir; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int EBUSY ; 
 int /*<<< orphan*/  NI_E_DMA_AI_AO_SEL_REG ; 
 int /*<<< orphan*/  NI_E_DMA_AI_SEL (unsigned int) ; 
 int /*<<< orphan*/  NI_E_DMA_AI_SEL_MASK ; 
 unsigned int NI_STC_DMA_CHAN_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mite_channel* mite_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_request_ai_mite_channel(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	struct mite_channel *mite_chan;
	unsigned long flags;
	unsigned int bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite, devpriv->ai_mite_ring);
	if (!mite_chan) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for analog input\n");
		return -EBUSY;
	}
	mite_chan->dir = COMEDI_INPUT;
	devpriv->ai_mite_chan = mite_chan;

	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_E_DMA_AI_AO_SEL_REG,
			NI_E_DMA_AI_SEL_MASK, NI_E_DMA_AI_SEL(bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}