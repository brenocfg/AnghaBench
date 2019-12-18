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
struct pci230_private {int hwver; } ;
struct pci230_board {scalar_t__ min_hwver; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct pci230_private* private; struct pci230_board* board_ptr; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; int start_arg; int scan_begin_arg; int scan_end_arg; scalar_t__ chanlist_len; int stop_arg; scalar_t__ chanlist; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* COMBINE (int,int /*<<< orphan*/ ,int) ; 
 int CR_EDGE ; 
 int CR_FLAGS_MASK ; 
 int CR_INVERT ; 
 int EINVAL ; 
 int MAX_SPEED_AO ; 
 int /*<<< orphan*/  MIN_SPEED_AO ; 
 unsigned int TRIG_COUNT ; 
#define  TRIG_EXT 129 
 int TRIG_INT ; 
 unsigned int TRIG_NONE ; 
 unsigned int TRIG_NOW ; 
#define  TRIG_TIMER 128 
 int comedi_check_trigger_arg_is (int*,scalar_t__) ; 
 int comedi_check_trigger_arg_max (int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_min (int*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,unsigned int) ; 
 int pci230_ao_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  pci230_ns_to_single_timer (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci230_ao_cmdtest(struct comedi_device *dev,
			     struct comedi_subdevice *s, struct comedi_cmd *cmd)
{
	const struct pci230_board *board = dev->board_ptr;
	struct pci230_private *devpriv = dev->private;
	int err = 0;
	unsigned int tmp;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);

	tmp = TRIG_TIMER | TRIG_INT;
	if (board->min_hwver > 0 && devpriv->hwver >= 2) {
		/*
		 * For PCI230+ hardware version 2 onwards, allow external
		 * trigger from EXTTRIG/EXTCONVCLK input (PCI230+ pin 25).
		 *
		 * FIXME: The permitted scan_begin_src values shouldn't depend
		 * on devpriv->hwver (the detected card's actual hardware
		 * version).  They should only depend on board->min_hwver
		 * (the static capabilities of the configured card).  To fix
		 * it, a new card model, e.g. "pci230+2" would have to be
		 * defined with min_hwver set to 2.  It doesn't seem worth it
		 * for this alone.  At the moment, please consider
		 * scan_begin_src==TRIG_EXT support to be a bonus rather than a
		 * guarantee!
		 */
		tmp |= TRIG_EXT;
	}
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, tmp);

	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

#define MAX_SPEED_AO	8000	/* 8000 ns => 125 kHz */
/*
 * Comedi limit due to unsigned int cmd.  Driver limit =
 * 2^16 (16bit * counter) * 1000000ns (1kHz onboard clock) = 65.536s
 */
#define MIN_SPEED_AO	4294967295u	/* 4294967295ns = 4.29s */

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    MAX_SPEED_AO);
		err |= comedi_check_trigger_arg_max(&cmd->scan_begin_arg,
						    MIN_SPEED_AO);
		break;
	case TRIG_EXT:
		/*
		 * External trigger - for PCI230+ hardware version 2 onwards.
		 */
		/* Trigger number must be 0. */
		if (cmd->scan_begin_arg & ~CR_FLAGS_MASK) {
			cmd->scan_begin_arg = COMBINE(cmd->scan_begin_arg, 0,
						      ~CR_FLAGS_MASK);
			err |= -EINVAL;
		}
		/*
		 * The only flags allowed are CR_EDGE and CR_INVERT.
		 * The CR_EDGE flag is ignored.
		 */
		if (cmd->scan_begin_arg & CR_FLAGS_MASK &
		    ~(CR_EDGE | CR_INVERT)) {
			cmd->scan_begin_arg =
			    COMBINE(cmd->scan_begin_arg, 0,
				    CR_FLAGS_MASK & ~(CR_EDGE | CR_INVERT));
			err |= -EINVAL;
		}
		break;
	default:
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
		break;
	}

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		tmp = cmd->scan_begin_arg;
		pci230_ns_to_single_timer(&cmd->scan_begin_arg, cmd->flags);
		if (tmp != cmd->scan_begin_arg)
			err++;
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists */
	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= pci230_ao_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}