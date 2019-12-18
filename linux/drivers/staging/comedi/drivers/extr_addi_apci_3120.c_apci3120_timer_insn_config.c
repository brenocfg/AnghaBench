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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; struct apci3120_private* private; } ;
struct apci3120_private {int ctrl; unsigned int mode; } ;

/* Variables and functions */
 int APCI3120_CTRL_GATE (int) ; 
 scalar_t__ APCI3120_MODE_REG ; 
 unsigned int APCI3120_MODE_TIMER2_AS_COUNTER ; 
 unsigned int APCI3120_MODE_TIMER2_AS_MASK ; 
 unsigned int APCI3120_MODE_TIMER2_AS_TIMER ; 
 unsigned int APCI3120_MODE_TIMER2_AS_WDOG ; 
 scalar_t__ APCI3120_STATUS_REG ; 
 unsigned int APCI3120_STATUS_TIMER2_INT ; 
 unsigned int APCI3120_TIMER_MODE0 ; 
 unsigned int APCI3120_TIMER_MODE2 ; 
 unsigned int APCI3120_TIMER_MODE4 ; 
 unsigned int APCI3120_TIMER_MODE5 ; 
 int /*<<< orphan*/  CMDF_ROUND_DOWN ; 
 unsigned int COMEDI_COUNTER_ARMED ; 
 unsigned int COMEDI_COUNTER_COUNTING ; 
 unsigned int COMEDI_COUNTER_TERMINAL_COUNT ; 
 int EINVAL ; 
#define  I8254_MODE0 135 
#define  I8254_MODE2 134 
#define  I8254_MODE4 133 
#define  I8254_MODE5 132 
#define  INSN_CONFIG_ARM 131 
#define  INSN_CONFIG_DISARM 130 
#define  INSN_CONFIG_GET_COUNTER_STATUS 129 
#define  INSN_CONFIG_SET_COUNTER_MODE 128 
 int /*<<< orphan*/  apci3120_clr_timer2_interrupt (struct comedi_device*) ; 
 unsigned int apci3120_ns_to_timer (struct comedi_device*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apci3120_timer_enable (struct comedi_device*,int,int) ; 
 int /*<<< orphan*/  apci3120_timer_set_mode (struct comedi_device*,int,unsigned int) ; 
 int /*<<< orphan*/  apci3120_timer_write (struct comedi_device*,int,unsigned int) ; 
 unsigned int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int apci3120_timer_insn_config(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	struct apci3120_private *devpriv = dev->private;
	unsigned int divisor;
	unsigned int status;
	unsigned int mode;
	unsigned int timer_mode;

	switch (data[0]) {
	case INSN_CONFIG_ARM:
		apci3120_clr_timer2_interrupt(dev);
		divisor = apci3120_ns_to_timer(dev, 2, data[1],
					       CMDF_ROUND_DOWN);
		apci3120_timer_write(dev, 2, divisor);
		apci3120_timer_enable(dev, 2, true);
		break;

	case INSN_CONFIG_DISARM:
		apci3120_timer_enable(dev, 2, false);
		apci3120_clr_timer2_interrupt(dev);
		break;

	case INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING |
			  COMEDI_COUNTER_TERMINAL_COUNT;

		if (devpriv->ctrl & APCI3120_CTRL_GATE(2)) {
			data[1] |= COMEDI_COUNTER_ARMED;
			data[1] |= COMEDI_COUNTER_COUNTING;
		}
		status = inw(dev->iobase + APCI3120_STATUS_REG);
		if (status & APCI3120_STATUS_TIMER2_INT) {
			data[1] &= ~COMEDI_COUNTER_COUNTING;
			data[1] |= COMEDI_COUNTER_TERMINAL_COUNT;
		}
		break;

	case INSN_CONFIG_SET_COUNTER_MODE:
		switch (data[1]) {
		case I8254_MODE0:
			mode = APCI3120_MODE_TIMER2_AS_COUNTER;
			timer_mode = APCI3120_TIMER_MODE0;
			break;
		case I8254_MODE2:
			mode = APCI3120_MODE_TIMER2_AS_TIMER;
			timer_mode = APCI3120_TIMER_MODE2;
			break;
		case I8254_MODE4:
			mode = APCI3120_MODE_TIMER2_AS_TIMER;
			timer_mode = APCI3120_TIMER_MODE4;
			break;
		case I8254_MODE5:
			mode = APCI3120_MODE_TIMER2_AS_WDOG;
			timer_mode = APCI3120_TIMER_MODE5;
			break;
		default:
			return -EINVAL;
		}
		apci3120_timer_enable(dev, 2, false);
		apci3120_clr_timer2_interrupt(dev);
		apci3120_timer_set_mode(dev, 2, timer_mode);
		devpriv->mode &= ~APCI3120_MODE_TIMER2_AS_MASK;
		devpriv->mode |= mode;
		outb(devpriv->mode, dev->iobase + APCI3120_MODE_REG);
		break;

	default:
		return -EINVAL;
	}

	return insn->n;
}