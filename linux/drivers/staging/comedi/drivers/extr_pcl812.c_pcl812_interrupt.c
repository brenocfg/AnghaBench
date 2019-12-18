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
struct pcl812_private {scalar_t__ ai_dma; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  attached; struct pcl812_private* private; struct comedi_subdevice* read_subdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl812_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl812_handle_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl812_handle_eoc (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static irqreturn_t pcl812_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->read_subdev;
	struct pcl812_private *devpriv = dev->private;

	if (!dev->attached) {
		pcl812_ai_clear_eoc(dev);
		return IRQ_HANDLED;
	}

	if (devpriv->ai_dma)
		pcl812_handle_dma(dev, s);
	else
		pcl812_handle_eoc(dev, s);

	pcl812_ai_clear_eoc(dev);

	comedi_handle_events(dev, s);
	return IRQ_HANDLED;
}