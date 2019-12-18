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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int comedi_buf_n_bytes_ready (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_handle_fifo_dregs (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_sync_ai_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ni_ai_poll(struct comedi_device *dev, struct comedi_subdevice *s)
{
	unsigned long flags;
	int count;

	/*  lock to avoid race with interrupt handler */
	spin_lock_irqsave(&dev->spinlock, flags);
#ifndef PCIDMA
	ni_handle_fifo_dregs(dev);
#else
	ni_sync_ai_dma(dev);
#endif
	count = comedi_buf_n_bytes_ready(s);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return count;
}