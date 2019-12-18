#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ni_private {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/ * gpct_mite_ring; int /*<<< orphan*/  mite; TYPE_1__* counter_dev; } ;
struct ni_gpct {int dummy; } ;
struct mite_channel {int dir; int /*<<< orphan*/  channel; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;
typedef  enum comedi_io_direction { ____Placeholder_comedi_io_direction } comedi_io_direction ;
struct TYPE_2__ {struct ni_gpct* counters; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NI_E_DMA_G0_G1_SEL (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  NI_E_DMA_G0_G1_SEL_MASK (unsigned int) ; 
 int /*<<< orphan*/  NI_E_DMA_G0_G1_SEL_REG ; 
 unsigned int NI_STC_DMA_CHAN_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mite_channel* mite_request_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (struct ni_gpct*,struct mite_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_request_gpct_mite_channel(struct comedi_device *dev,
					unsigned int gpct_index,
					enum comedi_io_direction direction)
{
	struct ni_private *devpriv = dev->private;
	struct ni_gpct *counter = &devpriv->counter_dev->counters[gpct_index];
	struct mite_channel *mite_chan;
	unsigned long flags;
	unsigned int bits;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	mite_chan = mite_request_channel(devpriv->mite,
					 devpriv->gpct_mite_ring[gpct_index]);
	if (!mite_chan) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev,
			"failed to reserve mite dma channel for counter\n");
		return -EBUSY;
	}
	mite_chan->dir = direction;
	ni_tio_set_mite_channel(counter, mite_chan);

	bits = NI_STC_DMA_CHAN_SEL(mite_chan->channel);
	ni_set_bitfield(dev, NI_E_DMA_G0_G1_SEL_REG,
			NI_E_DMA_G0_G1_SEL_MASK(gpct_index),
			NI_E_DMA_G0_G1_SEL(gpct_index, bits));

	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}