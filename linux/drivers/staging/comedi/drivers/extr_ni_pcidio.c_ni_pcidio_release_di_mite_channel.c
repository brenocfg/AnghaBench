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
struct nidio96_private {int /*<<< orphan*/  mite_channel_lock; int /*<<< orphan*/ * di_mite_chan; } ;
struct comedi_device {scalar_t__ mmio; struct nidio96_private* private; } ;

/* Variables and functions */
 scalar_t__ DMA_LINE_CONTROL_GROUP1 ; 
 int /*<<< orphan*/  mite_release_channel (int /*<<< orphan*/ *) ; 
 int primary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int secondary_DMAChannel_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ni_pcidio_release_di_mite_channel(struct comedi_device *dev)
{
	struct nidio96_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->di_mite_chan) {
		mite_release_channel(devpriv->di_mite_chan);
		devpriv->di_mite_chan = NULL;
		writeb(primary_DMAChannel_bits(0) |
		       secondary_DMAChannel_bits(0),
		       dev->mmio + DMA_LINE_CONTROL_GROUP1);
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
}