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
struct pcl816_private {unsigned int ai_poll_ptr; struct comedi_isadma* dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_isadma_desc {int /*<<< orphan*/  virt_addr; } ;
struct comedi_isadma {size_t cur_dma; struct comedi_isadma_desc* desc; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct pcl816_private* private; } ;

/* Variables and functions */
 int comedi_buf_n_bytes_ready (struct comedi_subdevice*) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int comedi_isadma_poll (struct comedi_isadma*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transfer_from_dma_buf (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int pcl816_ai_poll(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcl816_private *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_isadma_desc *desc;
	unsigned long flags;
	unsigned int poll;
	int ret;

	spin_lock_irqsave(&dev->spinlock, flags);

	poll = comedi_isadma_poll(dma);
	poll = comedi_bytes_to_samples(s, poll);
	if (poll > devpriv->ai_poll_ptr) {
		desc = &dma->desc[dma->cur_dma];
		transfer_from_dma_buf(dev, s, desc->virt_addr,
				      devpriv->ai_poll_ptr,
				      poll - devpriv->ai_poll_ptr);
		/* new buffer position */
		devpriv->ai_poll_ptr = poll;

		comedi_handle_events(dev, s);

		ret = comedi_buf_n_bytes_ready(s);
	} else {
		/* no new samples */
		ret = 0;
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return ret;
}