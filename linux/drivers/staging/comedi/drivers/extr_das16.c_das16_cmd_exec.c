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
struct TYPE_2__ {scalar_t__ expires; } ;
struct das16_private_struct {int timer_running; int ctrl_reg; scalar_t__ can_burst; TYPE_1__ timer; struct comedi_isadma* dma; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_isadma {scalar_t__ cur_dma; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct das16_private_struct* private; } ;
struct comedi_cmd {int chanlist_len; int flags; scalar_t__ convert_src; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CMDF_PRIORITY ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS1600_BURST_REG ; 
 unsigned int DAS1600_BURST_VAL ; 
 unsigned int DAS1600_CONV_DISABLE ; 
 scalar_t__ DAS1600_CONV_REG ; 
 int DAS16_CTRL_DMAE ; 
 int DAS16_CTRL_EXT_PACER ; 
 int DAS16_CTRL_INTE ; 
 int DAS16_CTRL_INT_PACER ; 
 int DAS16_CTRL_PACING_MASK ; 
 scalar_t__ DAS16_CTRL_REG ; 
 unsigned int DAS16_PACER_BURST_LEN (int) ; 
 scalar_t__ DAS16_PACER_REG ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  das16_ai_set_mux_range (struct comedi_device*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  das16_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das16_set_pacer (struct comedi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_period () ; 

__attribute__((used)) static int das16_cmd_exec(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct das16_private_struct *devpriv = dev->private;
	struct comedi_isadma *dma = devpriv->dma;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int first_chan = CR_CHAN(cmd->chanlist[0]);
	unsigned int last_chan = CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1]);
	unsigned int range = CR_RANGE(cmd->chanlist[0]);
	unsigned int byte;
	unsigned long flags;

	if (cmd->flags & CMDF_PRIORITY) {
		dev_err(dev->class_dev,
			"isa dma transfers cannot be performed with CMDF_PRIORITY, aborting\n");
		return -1;
	}

	if (devpriv->can_burst)
		outb(DAS1600_CONV_DISABLE, dev->iobase + DAS1600_CONV_REG);

	/* set mux and range for chanlist scan */
	das16_ai_set_mux_range(dev, first_chan, last_chan, range);

	/* set counter mode and counts */
	cmd->convert_arg = das16_set_pacer(dev, cmd->convert_arg, cmd->flags);

	/* enable counters */
	byte = 0;
	if (devpriv->can_burst) {
		if (cmd->convert_src == TRIG_NOW) {
			outb(DAS1600_BURST_VAL,
			     dev->iobase + DAS1600_BURST_REG);
			/*  set burst length */
			byte |= DAS16_PACER_BURST_LEN(cmd->chanlist_len - 1);
		} else {
			outb(0, dev->iobase + DAS1600_BURST_REG);
		}
	}
	outb(byte, dev->iobase + DAS16_PACER_REG);

	/* set up dma transfer */
	dma->cur_dma = 0;
	das16_ai_setup_dma(dev, s, 0);

	/*  set up timer */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->timer_running = 1;
	devpriv->timer.expires = jiffies + timer_period();
	add_timer(&devpriv->timer);

	/* enable DMA interrupt with external or internal pacing */
	devpriv->ctrl_reg &= ~(DAS16_CTRL_INTE | DAS16_CTRL_PACING_MASK);
	devpriv->ctrl_reg |= DAS16_CTRL_DMAE;
	if (cmd->convert_src == TRIG_EXT)
		devpriv->ctrl_reg |= DAS16_CTRL_EXT_PACER;
	else
		devpriv->ctrl_reg |= DAS16_CTRL_INT_PACER;
	outb(devpriv->ctrl_reg, dev->iobase + DAS16_CTRL_REG);

	if (devpriv->can_burst)
		outb(0, dev->iobase + DAS1600_CONV_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return 0;
}