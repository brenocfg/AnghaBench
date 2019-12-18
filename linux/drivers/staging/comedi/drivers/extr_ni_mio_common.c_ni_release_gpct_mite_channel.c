#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_private {int /*<<< orphan*/  mite_channel_lock; TYPE_1__* counter_dev; } ;
struct mite_channel {int dummy; } ;
struct comedi_device {struct ni_private* private; } ;
struct TYPE_4__ {struct mite_channel* mite_chan; } ;
struct TYPE_3__ {TYPE_2__* counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI_E_DMA_G0_G1_SEL_MASK (unsigned int) ; 
 int /*<<< orphan*/  NI_E_DMA_G0_G1_SEL_REG ; 
 int /*<<< orphan*/  mite_release_channel (struct mite_channel*) ; 
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_mite_channel (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ni_release_gpct_mite_channel(struct comedi_device *dev,
					 unsigned int gpct_index)
{
	struct ni_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->counter_dev->counters[gpct_index].mite_chan) {
		struct mite_channel *mite_chan =
		    devpriv->counter_dev->counters[gpct_index].mite_chan;

		ni_set_bitfield(dev, NI_E_DMA_G0_G1_SEL_REG,
				NI_E_DMA_G0_G1_SEL_MASK(gpct_index), 0);
		ni_tio_set_mite_channel(&devpriv->
					counter_dev->counters[gpct_index],
					NULL);
		mite_release_channel(mite_chan);
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);
}