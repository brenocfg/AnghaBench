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
struct pcl726_private {scalar_t__ cmd_running; } ;
struct comedi_subdevice {int /*<<< orphan*/  state; } ;
struct comedi_device {struct pcl726_private* private; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl726_intr_cancel (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static irqreturn_t pcl726_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	struct pcl726_private *devpriv = dev->private;

	if (devpriv->cmd_running) {
		pcl726_intr_cancel(dev, s);

		comedi_buf_write_samples(s, &s->state, 1);
		comedi_handle_events(dev, s);
	}

	return IRQ_HANDLED;
}