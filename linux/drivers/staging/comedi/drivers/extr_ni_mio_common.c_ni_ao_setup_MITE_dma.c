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
struct ni_private {int /*<<< orphan*/  mite_channel_lock; scalar_t__ ao_mite_chan; scalar_t__ is_6713; scalar_t__ is_611x; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct comedi_subdevice* write_subdev; struct ni_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  prealloc_bufsz; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  comedi_buf_read_alloc (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_arm (scalar_t__) ; 
 int /*<<< orphan*/  mite_prep_dma (scalar_t__,int,int) ; 
 int ni_request_ao_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_ao_setup_MITE_dma(struct comedi_device *dev)
{
	struct ni_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->write_subdev;
	int retval;
	unsigned long flags;

	retval = ni_request_ao_mite_channel(dev);
	if (retval)
		return retval;

	/* read alloc the entire buffer */
	comedi_buf_read_alloc(s, s->async->prealloc_bufsz);

	spin_lock_irqsave(&devpriv->mite_channel_lock, flags);
	if (devpriv->ao_mite_chan) {
		if (devpriv->is_611x || devpriv->is_6713) {
			mite_prep_dma(devpriv->ao_mite_chan, 32, 32);
		} else {
			/*
			 * Doing 32 instead of 16 bit wide transfers from
			 * memory makes the mite do 32 bit pci transfers,
			 * doubling pci bandwidth.
			 */
			mite_prep_dma(devpriv->ao_mite_chan, 16, 32);
		}
		mite_dma_arm(devpriv->ao_mite_chan);
	} else {
		retval = -EIO;
	}
	spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags);

	return retval;
}