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
struct pcmuio_asic {int active; int /*<<< orphan*/  spinlock; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct pcmuio_private* private; } ;
struct comedi_cmd {scalar_t__ start_src; } ;
struct TYPE_2__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_INT ; 
 int /*<<< orphan*/  pcmuio_inttrig_start_intr ; 
 int /*<<< orphan*/  pcmuio_start_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int pcmuio_subdevice_to_asic (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pcmuio_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pcmuio_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int asic = pcmuio_subdevice_to_asic(s);
	struct pcmuio_asic *chip = &devpriv->asics[asic];
	unsigned long flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	chip->active = 1;

	/* Set up start of acquisition. */
	if (cmd->start_src == TRIG_INT)
		s->async->inttrig = pcmuio_inttrig_start_intr;
	else	/* TRIG_NOW */
		pcmuio_start_intr(dev, s);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	return 0;
}