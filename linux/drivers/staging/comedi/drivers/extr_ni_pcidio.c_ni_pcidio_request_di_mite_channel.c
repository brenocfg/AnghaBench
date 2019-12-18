#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nidio96_private {int /*<<< orphan*/  mite_channel_lock; TYPE_1__* di_mite_chan; int /*<<< orphan*/  di_mite_ring; int /*<<< orphan*/  mite; } ;
struct comedi_device {scalar_t__ mmio; int /*<<< orphan*/  class_dev; struct nidio96_private* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (TYPE_1__*) ; 
 int /*<<< orphan*/  COMEDI_INPUT ; 
 scalar_t__ DMA_LINE_CONTROL_GROUP1 ; 
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mite_request_channel_in_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int primary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int secondary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int ni_pcidio_request_di_mite_channel(struct comedi_device *dev)
{
	struct nidio96_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	BUG_ON(devpriv->di_mite_chan);
	devpriv->di_mite_chan =
	    mite_request_channel_in_range(devpriv->mite,
					  devpriv->di_mite_ring, 1, 2);
	if (!devpriv->di_mite_chan) {
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
		dev_err(dev->class_dev, "failed to reserve mite dma channel\n");
		return -EBUSY;
	}
	devpriv->di_mite_chan->dir = COMEDI_INPUT;
	writeb(primary_DMAChannel_bits(devpriv->di_mite_chan->channel) |
	       secondary_DMAChannel_bits(devpriv->di_mite_chan->channel),
	       dev->mmio + DMA_LINE_CONTROL_GROUP1);
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
	return 0;
}