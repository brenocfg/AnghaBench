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
struct pcl818_private {unsigned int* act_chanlist; size_t act_chanlist_pos; size_t act_chanlist_len; scalar_t__ usefifo; scalar_t__ dma; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct pcl818_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static bool pcl818_ai_write_sample(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned int chan, unsigned int val)
{
	struct pcl818_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int expected_chan;

	expected_chan = devpriv->act_chanlist[devpriv->act_chanlist_pos];
	if (chan != expected_chan) {
		dev_dbg(dev->class_dev,
			"A/D mode1/3 %s - channel dropout %d!=%d !\n",
			(devpriv->dma) ? "DMA" :
			(devpriv->usefifo) ? "FIFO" : "IRQ",
			chan, expected_chan);
		s->async->events |= COMEDI_CB_ERROR;
		return false;
	}

	comedi_buf_write_samples(s, &val, 1);

	devpriv->act_chanlist_pos++;
	if (devpriv->act_chanlist_pos >= devpriv->act_chanlist_len)
		devpriv->act_chanlist_pos = 0;

	if (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_done >= cmd->stop_arg) {
		s->async->events |= COMEDI_CB_EOA;
		return false;
	}

	return true;
}