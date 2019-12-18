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
struct dt2811_private {unsigned int ai_divisor; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct dt2811_private* private; } ;
struct comedi_cmd {scalar_t__ start_src; scalar_t__ convert_src; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int DT2811_ADCSR_ADMODE (int) ; 
 unsigned int DT2811_ADCSR_INTENB ; 
 scalar_t__ DT2811_ADCSR_REG ; 
 scalar_t__ DT2811_TMRCTR_REG ; 
 scalar_t__ TRIG_NOW ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  dt2811_ai_set_chanspec (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int dt2811_ai_cmd(struct comedi_device *dev,
			 struct comedi_subdevice *s)
{
	struct dt2811_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int mode;

	if (cmd->start_src == TRIG_NOW) {
		/*
		 * Mode 1
		 * Continuous conversion, internal trigger and clock
		 *
		 * This resets the trigger flip-flop, disabling A/D strobes.
		 * The timer/counter register is loaded with the division
		 * ratio which will give the required sample rate.
		 *
		 * Loading the first chanspec sets the trigger flip-flop,
		 * enabling the timer/counter. A/D strobes are then generated
		 * at the rate set by the internal clock/divider.
		 */
		mode = DT2811_ADCSR_ADMODE(1);
	} else { /* TRIG_EXT */
		if (cmd->convert_src == TRIG_TIMER) {
			/*
			 * Mode 2
			 * Continuous conversion, external trigger
			 *
			 * Similar to Mode 1, with the exception that the
			 * trigger flip-flop must be set by a negative edge
			 * on the external trigger input.
			 */
			mode = DT2811_ADCSR_ADMODE(2);
		} else { /* TRIG_EXT */
			/*
			 * Mode 3
			 * Continuous conversion, external trigger, clock
			 *
			 * Similar to Mode 2, with the exception that the
			 * conversion rate is set by the frequency on the
			 * external clock/divider.
			 */
			mode = DT2811_ADCSR_ADMODE(3);
		}
	}
	outb(mode | DT2811_ADCSR_INTENB, dev->iobase + DT2811_ADCSR_REG);

	/* load timer */
	outb(devpriv->ai_divisor, dev->iobase + DT2811_TMRCTR_REG);

	/* load chanspec - enables timer */
	dt2811_ai_set_chanspec(dev, cmd->chanlist[0]);

	return 0;
}