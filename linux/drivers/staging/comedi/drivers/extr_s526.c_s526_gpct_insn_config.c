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
struct s526_private {unsigned int* gpct_config; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; struct s526_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int GPCT_RESET_COUNTER_ON_INDEX ; 
 unsigned int GPCT_X2 ; 
 unsigned int GPCT_X4 ; 
#define  INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR 130 
#define  INSN_CONFIG_GPCT_QUADRATURE_ENCODER 129 
#define  INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR 128 
 unsigned int S526_GPCT_CTRL_CT_LOAD ; 
 unsigned int S526_GPCT_CTRL_CT_RESET ; 
 scalar_t__ S526_GPCT_CTRL_REG (unsigned int) ; 
 unsigned int S526_GPCT_MODE_AUTOLOAD_IXRISE ; 
 unsigned int S526_GPCT_MODE_AUTOLOAD_MASK ; 
 unsigned int S526_GPCT_MODE_AUTOLOAD_NONE ; 
 unsigned int S526_GPCT_MODE_CLK_SRC_QUADX1 ; 
 unsigned int S526_GPCT_MODE_CLK_SRC_QUADX2 ; 
 unsigned int S526_GPCT_MODE_CLK_SRC_QUADX4 ; 
 unsigned int S526_GPCT_MODE_CTDIR_CTRL_QUAD ; 
 unsigned int S526_GPCT_MODE_PR_SELECT_MASK ; 
 unsigned int S526_GPCT_MODE_PR_SELECT_PR0 ; 
 unsigned int S526_GPCT_MODE_PR_SELECT_PR1 ; 
 scalar_t__ S526_GPCT_MODE_REG (unsigned int) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  s526_gpct_write (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int s526_gpct_insn_config(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	struct s526_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int val;

	/*
	 * Check what type of Counter the user requested
	 * data[0] contains the Application type
	 */
	switch (data[0]) {
	case INSN_CONFIG_GPCT_QUADRATURE_ENCODER:
		/*
		 * data[0]: Application Type
		 * data[1]: Counter Mode Register Value
		 * data[2]: Pre-load Register Value
		 * data[3]: Conter Control Register
		 */
		devpriv->gpct_config[chan] = data[0];

#if 1
		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/*  Reset the counter if it is software preload */
		if ((val & S526_GPCT_MODE_AUTOLOAD_MASK) ==
		    S526_GPCT_MODE_AUTOLOAD_NONE) {
			/*  Reset the counter */
			outw(S526_GPCT_CTRL_CT_RESET,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));
			/*
			 * Load the counter from PR0
			 * outw(S526_GPCT_CTRL_CT_LOAD,
			 *      dev->iobase + S526_GPCT_CTRL_REG(chan));
			 */
		}
#else
		val = S526_GPCT_MODE_CTDIR_CTRL_QUAD;

		/*  data[1] contains GPCT_X1, GPCT_X2 or GPCT_X4 */
		if (data[1] == GPCT_X2)
			val |= S526_GPCT_MODE_CLK_SRC_QUADX2;
		else if (data[1] == GPCT_X4)
			val |= S526_GPCT_MODE_CLK_SRC_QUADX4;
		else
			val |= S526_GPCT_MODE_CLK_SRC_QUADX1;

		/*  When to take into account the indexpulse: */
		/*
		 * if (data[2] == GPCT_IndexPhaseLowLow) {
		 * } else if (data[2] == GPCT_IndexPhaseLowHigh) {
		 * } else if (data[2] == GPCT_IndexPhaseHighLow) {
		 * } else if (data[2] == GPCT_IndexPhaseHighHigh) {
		 * }
		 */
		/*  Take into account the index pulse? */
		if (data[3] == GPCT_RESET_COUNTER_ON_INDEX) {
			/*  Auto load with INDEX^ */
			val |= S526_GPCT_MODE_AUTOLOAD_IXRISE;
		}

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/*  Load the pre-load register */
		s526_gpct_write(dev, chan, data[2]);

		/*  Write the Counter Control Register */
		if (data[3])
			outw(data[3] & 0xffff,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));

		/*  Reset the counter if it is software preload */
		if ((val & S526_GPCT_MODE_AUTOLOAD_MASK) ==
		    S526_GPCT_MODE_AUTOLOAD_NONE) {
			/*  Reset the counter */
			outw(S526_GPCT_CTRL_CT_RESET,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));
			/*  Load the counter from PR0 */
			outw(S526_GPCT_CTRL_CT_LOAD,
			     dev->iobase + S526_GPCT_CTRL_REG(chan));
		}
#endif
		break;

	case INSN_CONFIG_GPCT_SINGLE_PULSE_GENERATOR:
		/*
		 * data[0]: Application Type
		 * data[1]: Counter Mode Register Value
		 * data[2]: Pre-load Register 0 Value
		 * data[3]: Pre-load Register 1 Value
		 * data[4]: Conter Control Register
		 */
		devpriv->gpct_config[chan] = data[0];

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR0 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR0;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load register 0 */
		s526_gpct_write(dev, chan, data[2]);

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR1 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR1;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load register 1 */
		s526_gpct_write(dev, chan, data[3]);

		/*  Write the Counter Control Register */
		if (data[4]) {
			val = data[4] & 0xffff;
			outw(val, dev->iobase + S526_GPCT_CTRL_REG(chan));
		}
		break;

	case INSN_CONFIG_GPCT_PULSE_TRAIN_GENERATOR:
		/*
		 * data[0]: Application Type
		 * data[1]: Counter Mode Register Value
		 * data[2]: Pre-load Register 0 Value
		 * data[3]: Pre-load Register 1 Value
		 * data[4]: Conter Control Register
		 */
		devpriv->gpct_config[chan] = data[0];

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR0 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR0;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load register 0 */
		s526_gpct_write(dev, chan, data[2]);

		/*  Set Counter Mode Register */
		val = data[1] & 0xffff;
		/* Select PR1 */
		val &= ~S526_GPCT_MODE_PR_SELECT_MASK;
		val |= S526_GPCT_MODE_PR_SELECT_PR1;
		outw(val, dev->iobase + S526_GPCT_MODE_REG(chan));

		/* Load the pre-load register 1 */
		s526_gpct_write(dev, chan, data[3]);

		/*  Write the Counter Control Register */
		if (data[4]) {
			val = data[4] & 0xffff;
			outw(val, dev->iobase + S526_GPCT_CTRL_REG(chan));
		}
		break;

	default:
		return -EINVAL;
	}

	return insn->n;
}