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
struct comedi_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  pacer; struct cb_pcidas_private* private; struct cb_pcidas_board* board_ptr; } ;
struct comedi_cmd {int chanlist_len; scalar_t__ convert_src; scalar_t__ scan_begin_src; int flags; scalar_t__ start_src; int start_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct cb_pcidas_private {unsigned int ctrl; scalar_t__ pcibar1; scalar_t__ pcibar2; } ;
struct cb_pcidas_board {scalar_t__ is_1602; } ;

/* Variables and functions */
 scalar_t__ AREF_DIFF ; 
 int CMDF_WAKE_EOS ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_EDGE ; 
 int CR_INVERT ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIDAS_AI_FIFO_CLR_REG ; 
 unsigned int PCIDAS_AI_FIRST (int /*<<< orphan*/ ) ; 
 unsigned int PCIDAS_AI_GAIN (unsigned int) ; 
 unsigned int PCIDAS_AI_LAST (int /*<<< orphan*/ ) ; 
 unsigned int PCIDAS_AI_PACER_EXTP ; 
 unsigned int PCIDAS_AI_PACER_INT ; 
 scalar_t__ PCIDAS_AI_REG ; 
 unsigned int PCIDAS_AI_SE ; 
 unsigned int PCIDAS_AI_UNIP ; 
 scalar_t__ PCIDAS_CALIB_REG ; 
 unsigned int PCIDAS_CTRL_EOAI ; 
 unsigned int PCIDAS_CTRL_INTE ; 
 unsigned int PCIDAS_CTRL_INT_CLR ; 
 unsigned int PCIDAS_CTRL_INT_EOS ; 
 unsigned int PCIDAS_CTRL_INT_FHF ; 
 unsigned int PCIDAS_CTRL_INT_FNE ; 
 unsigned int PCIDAS_CTRL_INT_MASK ; 
 unsigned int PCIDAS_CTRL_LADFUL ; 
 scalar_t__ PCIDAS_CTRL_REG ; 
 unsigned int PCIDAS_TRIG_BURSTE ; 
 unsigned int PCIDAS_TRIG_CLR ; 
 unsigned int PCIDAS_TRIG_EN ; 
 unsigned int PCIDAS_TRIG_MODE ; 
 unsigned int PCIDAS_TRIG_POL ; 
 scalar_t__ PCIDAS_TRIG_REG ; 
 unsigned int PCIDAS_TRIG_SEL_EXT ; 
 unsigned int PCIDAS_TRIG_SEL_NONE ; 
 unsigned int PCIDAS_TRIG_SEL_SW ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_range_is_unipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cb_pcidas_ai_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	const struct cb_pcidas_board *board = dev->board_ptr;
	struct cb_pcidas_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int range0 = CR_RANGE(cmd->chanlist[0]);
	unsigned int bits;
	unsigned long flags;

	/*  make sure PCIDAS_CALIB_EN is disabled */
	outw(0, devpriv->pcibar1 + PCIDAS_CALIB_REG);
	/*  initialize before settings pacer source and count values */
	outw(PCIDAS_TRIG_SEL_NONE, devpriv->pcibar1 + PCIDAS_TRIG_REG);
	/*  clear fifo */
	outw(0, devpriv->pcibar2 + PCIDAS_AI_FIFO_CLR_REG);

	/*  set mux limits, gain and pacer source */
	bits = PCIDAS_AI_FIRST(CR_CHAN(cmd->chanlist[0])) |
	       PCIDAS_AI_LAST(CR_CHAN(cmd->chanlist[cmd->chanlist_len - 1])) |
	       PCIDAS_AI_GAIN(range0);
	/*  set unipolar/bipolar */
	if (comedi_range_is_unipolar(s, range0))
		bits |= PCIDAS_AI_UNIP;
	/*  set singleended/differential */
	if (CR_AREF(cmd->chanlist[0]) != AREF_DIFF)
		bits |= PCIDAS_AI_SE;
	/*  set pacer source */
	if (cmd->convert_src == TRIG_EXT || cmd->scan_begin_src == TRIG_EXT)
		bits |= PCIDAS_AI_PACER_EXTP;
	else
		bits |= PCIDAS_AI_PACER_INT;
	outw(bits, devpriv->pcibar1 + PCIDAS_AI_REG);

	/*  load counters */
	if (cmd->scan_begin_src == TRIG_TIMER ||
	    cmd->convert_src == TRIG_TIMER) {
		comedi_8254_update_divisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	}

	/*  enable interrupts */
	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->ctrl |= PCIDAS_CTRL_INTE;
	devpriv->ctrl &= ~PCIDAS_CTRL_INT_MASK;
	if (cmd->flags & CMDF_WAKE_EOS) {
		if (cmd->convert_src == TRIG_NOW && cmd->chanlist_len > 1) {
			/* interrupt end of burst */
			devpriv->ctrl |= PCIDAS_CTRL_INT_EOS;
		} else {
			/* interrupt fifo not empty */
			devpriv->ctrl |= PCIDAS_CTRL_INT_FNE;
		}
	} else {
		/* interrupt fifo half full */
		devpriv->ctrl |= PCIDAS_CTRL_INT_FHF;
	}

	/*  enable (and clear) interrupts */
	outw(devpriv->ctrl |
	     PCIDAS_CTRL_EOAI | PCIDAS_CTRL_INT_CLR | PCIDAS_CTRL_LADFUL,
	     devpriv->pcibar1 + PCIDAS_CTRL_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  set start trigger and burst mode */
	bits = 0;
	if (cmd->start_src == TRIG_NOW) {
		bits |= PCIDAS_TRIG_SEL_SW;
	} else {	/* TRIG_EXT */
		bits |= PCIDAS_TRIG_SEL_EXT | PCIDAS_TRIG_EN | PCIDAS_TRIG_CLR;
		if (board->is_1602) {
			if (cmd->start_arg & CR_INVERT)
				bits |= PCIDAS_TRIG_POL;
			if (cmd->start_arg & CR_EDGE)
				bits |= PCIDAS_TRIG_MODE;
		}
	}
	if (cmd->convert_src == TRIG_NOW && cmd->chanlist_len > 1)
		bits |= PCIDAS_TRIG_BURSTE;
	outw(bits, devpriv->pcibar1 + PCIDAS_TRIG_REG);

	return 0;
}