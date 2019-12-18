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
struct das16m1_private {unsigned int intr_ctrl; int /*<<< orphan*/  counter; int /*<<< orphan*/  initial_hw_count; scalar_t__ adc_count; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct das16m1_private* private; } ;
struct comedi_cmd {scalar_t__ convert_src; scalar_t__ start_src; int /*<<< orphan*/  chanlist_len; int /*<<< orphan*/  chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ DAS16M1_CLR_INTR_REG ; 
 unsigned int DAS16M1_CS_EXT_TRIG ; 
 scalar_t__ DAS16M1_CS_REG ; 
 unsigned int DAS16M1_INTR_CTRL_INTE ; 
 unsigned int DAS16M1_INTR_CTRL_PACER_EXT ; 
 unsigned int DAS16M1_INTR_CTRL_PACER_INT ; 
 unsigned int DAS16M1_INTR_CTRL_PACER_MASK ; 
 scalar_t__ DAS16M1_INTR_CTRL_REG ; 
 int I8254_BINARY ; 
 int I8254_MODE2 ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  comedi_8254_set_mode (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_8254_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das16m1_ai_set_queue (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int das16m1_ai_cmd(struct comedi_device *dev,
			  struct comedi_subdevice *s)
{
	struct das16m1_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int byte;

	/*  set software count */
	devpriv->adc_count = 0;

	/*
	 * Initialize lower half of hardware counter, used to determine how
	 * many samples are in fifo.  Value doesn't actually load into counter
	 * until counter's next clock (the next a/d conversion).
	 */
	comedi_8254_set_mode(devpriv->counter, 1, I8254_MODE2 | I8254_BINARY);
	comedi_8254_write(devpriv->counter, 1, 0);

	/*
	 * Remember current reading of counter so we know when counter has
	 * actually been loaded.
	 */
	devpriv->initial_hw_count = comedi_8254_read(devpriv->counter, 1);

	das16m1_ai_set_queue(dev, cmd->chanlist, cmd->chanlist_len);

	/* enable interrupts and set internal pacer counter mode and counts */
	devpriv->intr_ctrl &= ~DAS16M1_INTR_CTRL_PACER_MASK;
	if (cmd->convert_src == TRIG_TIMER) {
		comedi_8254_update_divisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
		devpriv->intr_ctrl |= DAS16M1_INTR_CTRL_PACER_INT;
	} else {	/* TRIG_EXT */
		devpriv->intr_ctrl |= DAS16M1_INTR_CTRL_PACER_EXT;
	}

	/*  set control & status register */
	byte = 0;
	/*
	 * If we are using external start trigger (also board dislikes having
	 * both start and conversion triggers external simultaneously).
	 */
	if (cmd->start_src == TRIG_EXT && cmd->convert_src != TRIG_EXT)
		byte |= DAS16M1_CS_EXT_TRIG;

	outb(byte, dev->iobase + DAS16M1_CS_REG);

	/* clear interrupt */
	outb(0, dev->iobase + DAS16M1_CLR_INTR_REG);

	devpriv->intr_ctrl |= DAS16M1_INTR_CTRL_INTE;
	outb(devpriv->intr_ctrl, dev->iobase + DAS16M1_INTR_CTRL_REG);

	return 0;
}