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
struct me4000_private {unsigned int ai_init_ticks; int ai_scan_ticks; int ai_chan_ticks; unsigned int ai_ctrl_mode; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct me4000_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; unsigned int chanlist_len; unsigned int stop_arg; scalar_t__ scan_end_src; unsigned int scan_end_arg; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ ME4000_AI_CHAN_PRE_TIMER_REG ; 
 scalar_t__ ME4000_AI_CHAN_TIMER_REG ; 
 unsigned int ME4000_AI_CTRL_CHANNEL_FIFO ; 
 unsigned int ME4000_AI_CTRL_DATA_FIFO ; 
 unsigned int ME4000_AI_CTRL_HF_IRQ ; 
 scalar_t__ ME4000_AI_CTRL_REG ; 
 unsigned int ME4000_AI_CTRL_SC_IRQ ; 
 scalar_t__ ME4000_AI_SAMPLE_COUNTER_REG ; 
 scalar_t__ ME4000_AI_SCAN_PRE_TIMER_HIGH_REG ; 
 scalar_t__ ME4000_AI_SCAN_PRE_TIMER_LOW_REG ; 
 scalar_t__ ME4000_AI_SCAN_TIMER_HIGH_REG ; 
 scalar_t__ ME4000_AI_SCAN_TIMER_LOW_REG ; 
 scalar_t__ ME4000_AI_START_REG ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_NONE ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  me4000_ai_write_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int me4000_ai_do_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct me4000_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ctrl;

	/* Write timer arguments */
	outl(devpriv->ai_init_ticks - 1,
	     dev->iobase + ME4000_AI_SCAN_PRE_TIMER_LOW_REG);
	outl(0x0, dev->iobase + ME4000_AI_SCAN_PRE_TIMER_HIGH_REG);

	if (devpriv->ai_scan_ticks) {
		outl(devpriv->ai_scan_ticks - 1,
		     dev->iobase + ME4000_AI_SCAN_TIMER_LOW_REG);
		outl(0x0, dev->iobase + ME4000_AI_SCAN_TIMER_HIGH_REG);
	}

	outl(devpriv->ai_chan_ticks - 1,
	     dev->iobase + ME4000_AI_CHAN_PRE_TIMER_REG);
	outl(devpriv->ai_chan_ticks - 1,
	     dev->iobase + ME4000_AI_CHAN_TIMER_REG);

	/* Start sources */
	ctrl = devpriv->ai_ctrl_mode |
	       ME4000_AI_CTRL_CHANNEL_FIFO |
	       ME4000_AI_CTRL_DATA_FIFO;

	/* Stop triggers */
	if (cmd->stop_src == TRIG_COUNT) {
		outl(cmd->chanlist_len * cmd->stop_arg,
		     dev->iobase + ME4000_AI_SAMPLE_COUNTER_REG);
		ctrl |= ME4000_AI_CTRL_SC_IRQ;
	} else if (cmd->stop_src == TRIG_NONE &&
		   cmd->scan_end_src == TRIG_COUNT) {
		outl(cmd->scan_end_arg,
		     dev->iobase + ME4000_AI_SAMPLE_COUNTER_REG);
		ctrl |= ME4000_AI_CTRL_SC_IRQ;
	}
	ctrl |= ME4000_AI_CTRL_HF_IRQ;

	/* Write the setup to the control register */
	outl(ctrl, dev->iobase + ME4000_AI_CTRL_REG);

	/* Write the channel list */
	me4000_ai_write_chanlist(dev, s, cmd);

	/* Start acquistion by dummy read */
	inl(dev->iobase + ME4000_AI_START_REG);

	return 0;
}