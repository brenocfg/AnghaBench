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
struct pci230_private {scalar_t__ hwver; } ;
struct pci230_board {scalar_t__ min_hwver; scalar_t__ have_dio; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct pci230_private* private; struct pci230_board* board_ptr; } ;
struct comedi_cmd {unsigned int start_src; unsigned int scan_begin_src; unsigned int convert_src; unsigned int scan_end_src; unsigned int stop_src; int start_arg; scalar_t__ chanlist_len; int convert_arg; int scan_end_arg; int stop_arg; int scan_begin_arg; int /*<<< orphan*/ * chanlist; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ AREF_DIFF ; 
 int /*<<< orphan*/  CMDF_ROUND_UP ; 
 void* COMBINE (int,int,int) ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 int CR_EDGE ; 
 int CR_FLAGS_MASK ; 
 int CR_INVERT ; 
 int EINVAL ; 
 unsigned int MAX_SPEED_AI_DIFF ; 
 unsigned int MAX_SPEED_AI_PLUS ; 
 unsigned int MAX_SPEED_AI_SE ; 
 int MIN_SPEED_AI ; 
 unsigned int TRIG_COUNT ; 
 unsigned int TRIG_EXT ; 
 unsigned int TRIG_FOLLOW ; 
 unsigned int TRIG_INT ; 
 unsigned int TRIG_NONE ; 
 unsigned int TRIG_NOW ; 
 unsigned int TRIG_TIMER ; 
 int comedi_check_trigger_arg_is (int*,scalar_t__) ; 
 int comedi_check_trigger_arg_max (int*,int) ; 
 int comedi_check_trigger_arg_min (int*,int) ; 
 int comedi_check_trigger_is_unique (unsigned int) ; 
 int comedi_check_trigger_src (unsigned int*,unsigned int) ; 
 int pci230_ai_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  pci230_ai_check_scan_period (struct comedi_cmd*) ; 
 int /*<<< orphan*/  pci230_ns_to_single_timer (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci230_ai_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	const struct pci230_board *board = dev->board_ptr;
	struct pci230_private *devpriv = dev->private;
	int err = 0;
	unsigned int tmp;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW | TRIG_INT);

	tmp = TRIG_FOLLOW | TRIG_TIMER | TRIG_INT;
	if (board->have_dio || board->min_hwver > 0) {
		/*
		 * Unfortunately, we cannot trigger a scan off an external
		 * source on the PCI260 board, since it uses the PPIC0 (DIO)
		 * input, which isn't present on the PCI260.  For PCI260+
		 * we can use the EXTTRIG/EXTCONVCLK input on pin 17 instead.
		 */
		tmp |= TRIG_EXT;
	}
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, tmp);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_TIMER | TRIG_INT | TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	/*
	 * If scan_begin_src is not TRIG_FOLLOW, then a monostable will be
	 * set up to generate a fixed number of timed conversion pulses.
	 */
	if (cmd->scan_begin_src != TRIG_FOLLOW &&
	    cmd->convert_src != TRIG_TIMER)
		err |= -EINVAL;

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

#define MAX_SPEED_AI_SE		3200	/* PCI230 SE:   3200 ns => 312.5 kHz */
#define MAX_SPEED_AI_DIFF	8000	/* PCI230 DIFF: 8000 ns => 125 kHz */
#define MAX_SPEED_AI_PLUS	4000	/* PCI230+:     4000 ns => 250 kHz */
/*
 * Comedi limit due to unsigned int cmd.  Driver limit =
 * 2^16 (16bit * counter) * 1000000ns (1kHz onboard clock) = 65.536s
 */
#define MIN_SPEED_AI	4294967295u	/* 4294967295ns = 4.29s */

	if (cmd->convert_src == TRIG_TIMER) {
		unsigned int max_speed_ai;

		if (devpriv->hwver == 0) {
			/*
			 * PCI230 or PCI260.  Max speed depends whether
			 * single-ended or pseudo-differential.
			 */
			if (cmd->chanlist && cmd->chanlist_len > 0) {
				/* Peek analogue reference of first channel. */
				if (CR_AREF(cmd->chanlist[0]) == AREF_DIFF)
					max_speed_ai = MAX_SPEED_AI_DIFF;
				else
					max_speed_ai = MAX_SPEED_AI_SE;

			} else {
				/* No channel list.  Assume single-ended. */
				max_speed_ai = MAX_SPEED_AI_SE;
			}
		} else {
			/* PCI230+ or PCI260+. */
			max_speed_ai = MAX_SPEED_AI_PLUS;
		}

		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    max_speed_ai);
		err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
						    MIN_SPEED_AI);
	} else if (cmd->convert_src == TRIG_EXT) {
		/*
		 * external trigger
		 *
		 * convert_arg == (CR_EDGE | 0)
		 *                => trigger on +ve edge.
		 * convert_arg == (CR_EDGE | CR_INVERT | 0)
		 *                => trigger on -ve edge.
		 */
		if (cmd->convert_arg & CR_FLAGS_MASK) {
			/* Trigger number must be 0. */
			if (cmd->convert_arg & ~CR_FLAGS_MASK) {
				cmd->convert_arg = COMBINE(cmd->convert_arg, 0,
							   ~CR_FLAGS_MASK);
				err |= -EINVAL;
			}
			/*
			 * The only flags allowed are CR_INVERT and CR_EDGE.
			 * CR_EDGE is required.
			 */
			if ((cmd->convert_arg & CR_FLAGS_MASK & ~CR_INVERT) !=
			    CR_EDGE) {
				/* Set CR_EDGE, preserve CR_INVERT. */
				cmd->convert_arg =
				    COMBINE(cmd->start_arg, CR_EDGE | 0,
					    CR_FLAGS_MASK & ~CR_INVERT);
				err |= -EINVAL;
			}
		} else {
			/*
			 * Backwards compatibility with previous versions:
			 * convert_arg == 0 => trigger on -ve edge.
			 * convert_arg == 1 => trigger on +ve edge.
			 */
			err |= comedi_check_trigger_arg_max(&cmd->convert_arg,
							    1);
		}
	} else {
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	}

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (cmd->scan_begin_src == TRIG_EXT) {
		/*
		 * external "trigger" to begin each scan:
		 * scan_begin_arg==0 => use PPC0 input -> gate of CT0 -> gate
		 * of CT2 (sample convert trigger is CT2)
		 */
		if (cmd->scan_begin_arg & ~CR_FLAGS_MASK) {
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      ~CR_FLAGS_MASK);
			err |= -EINVAL;
		}
		/* The only flag allowed is CR_EDGE, which is ignored. */
		if (cmd->scan_begin_arg & CR_FLAGS_MASK & ~CR_EDGE) {
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      CR_FLAGS_MASK & ~CR_EDGE);
			err |= -EINVAL;
		}
	} else if (cmd->scan_begin_src == TRIG_TIMER) {
		/* N.B. cmd->convert_arg is also TRIG_TIMER */
		if (!pci230_ai_check_scan_period(cmd))
			err |= -EINVAL;

	} else {
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	}

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	if (cmd->convert_src == TRIG_TIMER) {
		tmp = cmd->convert_arg;
		pci230_ns_to_single_timer(&cmd->convert_arg, cmd->flags);
		if (tmp != cmd->convert_arg)
			err++;
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* N.B. cmd->convert_arg is also TRIG_TIMER */
		tmp = cmd->scan_begin_arg;
		pci230_ns_to_single_timer(&cmd->scan_begin_arg, cmd->flags);
		if (!pci230_ai_check_scan_period(cmd)) {
			/* Was below minimum required.  Round up. */
			pci230_ns_to_single_timer(&cmd->scan_begin_arg,
						  CMDF_ROUND_UP);
			pci230_ai_check_scan_period(cmd);
		}
		if (tmp != cmd->scan_begin_arg)
			err++;
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists */
	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci230_ai_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}