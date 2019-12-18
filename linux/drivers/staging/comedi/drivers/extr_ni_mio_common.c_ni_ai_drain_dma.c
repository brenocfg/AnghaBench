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
struct ni_private {int /*<<< orphan*/  mite_channel_lock; scalar_t__ ai_mite_chan; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 int NISTC_AI_STATUS1_FIFO_E ; 
 int /*<<< orphan*/  NISTC_AI_STATUS1_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mite_bytes_in_transit (scalar_t__) ; 
 int ni_stc_readw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_sync_ai_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ni_ai_drain_dma(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	int i;
	static const int timeout = 10000;
	unsigned long flags;
	int retval = 0;

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->ai_mite_chan) {
		for (i = 0; i < timeout; i++) {
			if ((ni_stc_readw(dev, NISTC_AI_STATUS1_REG) &
			     NISTC_AI_STATUS1_FIFO_E) &&
			    mite_bytes_in_transit(devpriv->ai_mite_chan) == 0)
				break;
			udelay(5);
		}
		if (i == timeout) {
			dev_err(dev->class_dev, "timed out\n");
			dev_err(dev->class_dev,
				"mite_bytes_in_transit=%i, AI_Status1_Register=0x%x\n",
				mite_bytes_in_transit(devpriv->ai_mite_chan),
				ni_stc_readw(dev, NISTC_AI_STATUS1_REG));
			retval = -1;
		}
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	ni_sync_ai_dma(dev);

	return retval;
}