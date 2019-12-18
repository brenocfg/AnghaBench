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
struct nidio96_private {int /*<<< orphan*/  mite_channel_lock; scalar_t__ di_mite_chan; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct nidio96_private* private; } ;

/* Variables and functions */
 int comedi_buf_n_bytes_ready (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  mite_sync_dma (scalar_t__,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_pcidio_poll(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct nidio96_private *devpriv = dev->private;
	unsigned long irq_flags;
	int count;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	spin_lock(&devpriv->mite_channel_lock);
	if (devpriv->di_mite_chan)
		mite_sync_dma(devpriv->di_mite_chan, s);
	spin_unlock(&devpriv->mite_channel_lock);
	count = comedi_buf_n_bytes_ready(s);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);
	return count;
}