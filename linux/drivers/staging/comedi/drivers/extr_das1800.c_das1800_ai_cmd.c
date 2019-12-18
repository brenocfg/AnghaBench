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
struct das1800_private {int irq_dma_bits; int dma_bits; int /*<<< orphan*/  ai_is_unipolar; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct das1800_private* private; } ;
struct comedi_cmd {int flags; scalar_t__ stop_src; scalar_t__ start_src; int start_arg; int stop_arg; scalar_t__ scan_begin_src; scalar_t__ convert_src; int chanlist_len; int convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int ATEN ; 
 int BMDE ; 
 int CGEN ; 
 int CGSL ; 
 int CMDF_PRIORITY ; 
 int CMDF_WAKE_EOS ; 
 int CR_INVERT ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int CVEN ; 
 scalar_t__ DAS1800_BURST_LENGTH ; 
 scalar_t__ DAS1800_BURST_RATE ; 
 scalar_t__ DAS1800_CONTROL_A ; 
 scalar_t__ DAS1800_CONTROL_B ; 
 scalar_t__ DAS1800_CONTROL_C ; 
 scalar_t__ DAS1800_STATUS ; 
 int DMA_ENABLED ; 
 int FFEN ; 
 int FIMD ; 
 int I8254_BINARY ; 
 int I8254_MODE0 ; 
 int IPCLK ; 
 int TGEN ; 
 int TGPL ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_TIMER ; 
 int XPCLK ; 
 int /*<<< orphan*/  comedi_8254_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  comedi_8254_pacer_enable (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  comedi_8254_update_divisors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_range_is_unipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  das1800_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int das1800_ai_chanspec_bits (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  das1800_ai_set_chanlist (struct comedi_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  das1800_ai_setup_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int das1800_ai_cmd(struct comedi_device *dev,
			  struct comedi_subdevice *s)
{
	struct das1800_private *devpriv = dev->private;
	int control_a, control_c;
	struct comedi_async *async = s->async;
	const struct comedi_cmd *cmd = &async->cmd;
	unsigned int range0 = CR_RANGE(cmd->chanlist[0]);

	/*
	 * Disable dma on CMDF_WAKE_EOS, or CMDF_PRIORITY (because dma in
	 * handler is unsafe at hard real-time priority).
	 */
	if (cmd->flags & (CMDF_WAKE_EOS | CMDF_PRIORITY))
		devpriv->irq_dma_bits &= ~DMA_ENABLED;
	else
		devpriv->irq_dma_bits |= devpriv->dma_bits;
	/*  interrupt on end of conversion for CMDF_WAKE_EOS */
	if (cmd->flags & CMDF_WAKE_EOS) {
		/*  interrupt fifo not empty */
		devpriv->irq_dma_bits &= ~FIMD;
	} else {
		/*  interrupt fifo half full */
		devpriv->irq_dma_bits |= FIMD;
	}

	das1800_ai_cancel(dev, s);

	devpriv->ai_is_unipolar = comedi_range_is_unipolar(s, range0);

	control_a = FFEN;
	if (cmd->stop_src == TRIG_EXT)
		control_a |= ATEN;
	if (cmd->start_src == TRIG_EXT)
		control_a |= TGEN | CGSL;
	else /* TRIG_NOW */
		control_a |= CGEN;
	if (control_a & (ATEN | TGEN)) {
		if ((cmd->start_arg & CR_INVERT) || (cmd->stop_arg & CR_INVERT))
			control_a |= TGPL;
	}

	control_c = das1800_ai_chanspec_bits(s, cmd->chanlist[0]);
	/* set clock source to internal or external */
	if (cmd->scan_begin_src == TRIG_FOLLOW) {
		/* not in burst mode */
		if (cmd->convert_src == TRIG_TIMER) {
			/* trig on cascaded counters */
			control_c |= IPCLK;
		} else { /* TRIG_EXT */
			/* trig on falling edge of external trigger */
			control_c |= XPCLK;
		}
	} else if (cmd->scan_begin_src == TRIG_TIMER) {
		/* burst mode with internal pacer clock */
		control_c |= BMDE | IPCLK;
	} else { /* TRIG_EXT */
		/* burst mode with external trigger */
		control_c |= BMDE | XPCLK;
	}

	das1800_ai_set_chanlist(dev, cmd->chanlist, cmd->chanlist_len);

	/* setup cascaded counters for conversion/scan frequency */
	if ((cmd->scan_begin_src == TRIG_FOLLOW ||
	     cmd->scan_begin_src == TRIG_TIMER) &&
	    cmd->convert_src == TRIG_TIMER) {
		comedi_8254_update_divisors(dev->pacer);
		comedi_8254_pacer_enable(dev->pacer, 1, 2, true);
	}

	/* setup counter 0 for 'about triggering' */
	if (cmd->stop_src == TRIG_EXT)
		comedi_8254_load(dev->pacer, 0, 1, I8254_MODE0 | I8254_BINARY);

	das1800_ai_setup_dma(dev, s);
	outb(control_c, dev->iobase + DAS1800_CONTROL_C);
	/*  set conversion rate and length for burst mode */
	if (control_c & BMDE) {
		outb(cmd->convert_arg / 1000 - 1,	/* microseconds - 1 */
		     dev->iobase + DAS1800_BURST_RATE);
		outb(cmd->chanlist_len - 1, dev->iobase + DAS1800_BURST_LENGTH);
	}

	/* enable and start conversions */
	outb(devpriv->irq_dma_bits, dev->iobase + DAS1800_CONTROL_B);
	outb(control_a, dev->iobase + DAS1800_CONTROL_A);
	outb(CVEN, dev->iobase + DAS1800_STATUS);

	return 0;
}