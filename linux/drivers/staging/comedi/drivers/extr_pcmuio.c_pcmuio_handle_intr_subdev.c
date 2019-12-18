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
struct pcmuio_private {struct pcmuio_asic* asics; } ;
struct pcmuio_asic {unsigned int enabled_mask; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  active; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pcmuio_private* private; } ;
struct comedi_cmd {unsigned int chanlist_len; scalar_t__ stop_src; scalar_t__ stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {scalar_t__ scans_done; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned int*,int) ; 
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pcmuio_handle_intr_subdev(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      unsigned int triggered)
{
	struct pcmuio_private *devpriv = dev->private;
	int asic = pcmuio_subdevice_to_asic(s);
	struct pcmuio_asic *chip = &devpriv->asics[asic];
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int val = 0;
	unsigned long flags;
	unsigned int i;

	spin_lock_irqsave(&chip->spinlock, flags);

	if (!chip->active)
		goto done;

	if (!(triggered & chip->enabled_mask))
		goto done;

	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);

		if (triggered & (1 << chan))
			val |= (1 << i);
	}

	comedi_buf_write_samples(s, &val, 1);

	if (cmd->stop_src == TRIG_COUNT &&
	    s->async->scans_done >= cmd->stop_arg)
		s->async->events |= COMEDI_CB_EOA;

done:
	spin_unlock_irqrestore(&chip->spinlock, flags);

	comedi_handle_events(dev, s);
}