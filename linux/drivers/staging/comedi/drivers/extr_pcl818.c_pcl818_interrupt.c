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
struct pcl818_private {scalar_t__ usefifo; scalar_t__ dma; scalar_t__ ai_cmd_canceled; int /*<<< orphan*/  ai_cmd_running; } ;
struct comedi_subdevice {int /*<<< orphan*/  (* cancel ) (struct comedi_device*,struct comedi_subdevice*) ;TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  attached; struct comedi_subdevice* read_subdev; struct pcl818_private* private; } ;
struct comedi_cmd {int /*<<< orphan*/  stop_arg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  scans_done; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl818_ai_clear_eoc (struct comedi_device*) ; 
 int /*<<< orphan*/  pcl818_handle_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl818_handle_eoc (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcl818_handle_fifo (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static irqreturn_t pcl818_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct pcl818_private *devpriv = dev->private;
	struct comedi_subdevice *s = dev->read_subdev;
	struct comedi_cmd *cmd = &s->async->cmd;

	if (!dev->attached || !devpriv->ai_cmd_running) {
		pcl818_ai_clear_eoc(dev);
		return IRQ_HANDLED;
	}

	if (devpriv->ai_cmd_canceled) {
		/*
		 * The cleanup from ai_cancel() has been delayed
		 * until now because the card doesn't seem to like
		 * being reprogrammed while a DMA transfer is in
		 * progress.
		 */
		s->async->scans_done = cmd->stop_arg;
		s->cancel(dev, s);
		return IRQ_HANDLED;
	}

	if (devpriv->dma)
		pcl818_handle_dma(dev, s);
	else if (devpriv->usefifo)
		pcl818_handle_fifo(dev, s);
	else
		pcl818_handle_eoc(dev, s);

	pcl818_ai_clear_eoc(dev);

	comedi_handle_events(dev, s);
	return IRQ_HANDLED;
}