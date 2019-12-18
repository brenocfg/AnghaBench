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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  class_dev; struct cb_pcidas_private* private; } ;
struct comedi_cmd {unsigned int chanlist_len; int scan_begin_src; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;
struct cb_pcidas_private {int /*<<< orphan*/  ao_ctrl; int /*<<< orphan*/  ao_pacer; scalar_t__ pcibar4; scalar_t__ pcibar1; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIDAS_AO_CHAN_EN (unsigned int) ; 
 scalar_t__ PCIDAS_AO_FIFO_CLR_REG ; 
 int /*<<< orphan*/  PCIDAS_AO_PACER_EXTP ; 
 int /*<<< orphan*/  PCIDAS_AO_PACER_INT ; 
 int /*<<< orphan*/  PCIDAS_AO_RANGE (unsigned int,unsigned int) ; 
 scalar_t__ PCIDAS_AO_REG ; 
#define  TRIG_EXT 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  cb_pcidas_ao_inttrig ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ao_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct cb_pcidas_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int i;
	unsigned long flags;

	/*  set channel limits, gain */
	spin_lock_irqsave(&dev->spinlock, flags);
	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int range = CR_RANGE(cmd->chanlist[i]);

		/*  enable channel */
		devpriv->ao_ctrl |= PCIDAS_AO_CHAN_EN(chan);
		/*  set range */
		devpriv->ao_ctrl |= PCIDAS_AO_RANGE(chan, range);
	}

	/*  disable analog out before settings pacer source and count values */
	outw(devpriv->ao_ctrl, devpriv->pcibar1 + PCIDAS_AO_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  clear fifo */
	outw(0, devpriv->pcibar4 + PCIDAS_AO_FIFO_CLR_REG);

	/*  load counters */
	if (cmd->scan_begin_src == TRIG_TIMER) {
		comedi_8254_update_divisors(devpriv->ao_pacer);
		comedi_8254_pacer_enable(devpriv->ao_pacer, 1, 2, true);
	}

	/*  set pacer source */
	spin_lock_irqsave(&dev->spinlock, flags);
	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		devpriv->ao_ctrl |= PCIDAS_AO_PACER_INT;
		break;
	case TRIG_EXT:
		devpriv->ao_ctrl |= PCIDAS_AO_PACER_EXTP;
		break;
	default:
		spin_unlock_irqrestore(&dev->spinlock, flags);
		dev_err(dev->class_dev, "error setting dac pacer source\n");
		return -1;
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	async->inttrig = cb_pcidas_ao_inttrig;

	return 0;
}