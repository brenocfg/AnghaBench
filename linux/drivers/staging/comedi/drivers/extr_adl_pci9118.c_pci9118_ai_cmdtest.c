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
struct pci9118_private {unsigned int ai_ns_min; scalar_t__ master; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  pacer; struct pci9118_private* private; } ;
struct comedi_cmd {unsigned int start_src; unsigned int scan_begin_src; unsigned int convert_src; unsigned int scan_end_src; unsigned int stop_src; unsigned int start_arg; unsigned int scan_begin_arg; int scan_end_arg; unsigned int convert_arg; unsigned int stop_arg; unsigned int chanlist_len; scalar_t__ chanlist; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TRIG_COUNT ; 
#define  TRIG_EXT 130 
 unsigned int TRIG_FOLLOW ; 
#define  TRIG_INT 129 
 unsigned int TRIG_NONE ; 
#define  TRIG_NOW 128 
 unsigned int TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_max (int*,int) ; 
 int comedi_check_trigger_arg_min (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_is_unique (unsigned int) ; 
 int comedi_check_trigger_src (unsigned int*,unsigned int) ; 
 int pci9118_ai_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 

__attribute__((used)) static int pci9118_ai_cmdtest(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_cmd *cmd)
{
	struct pci9118_private *devpriv = dev->private;
	int err = 0;
	unsigned int flags;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src,
					TRIG_NOW | TRIG_EXT | TRIG_INT);

	flags = TRIG_FOLLOW;
	if (devpriv->master)
		flags |= TRIG_TIMER | TRIG_EXT;
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, flags);

	flags = TRIG_TIMER | TRIG_EXT;
	if (devpriv->master)
		flags |= TRIG_NOW;
	err |= comedi_check_trigger_src(&cmd->convert_src, flags);

	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src,
					TRIG_COUNT | TRIG_NONE | TRIG_EXT);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->scan_begin_src);
	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	if (cmd->start_src == TRIG_EXT && cmd->scan_begin_src == TRIG_EXT)
		err |= -EINVAL;

	if ((cmd->scan_begin_src & (TRIG_TIMER | TRIG_EXT)) &&
	    (!(cmd->convert_src & (TRIG_TIMER | TRIG_NOW))))
		err |= -EINVAL;

	if ((cmd->scan_begin_src == TRIG_FOLLOW) &&
	    (!(cmd->convert_src & (TRIG_TIMER | TRIG_EXT))))
		err |= -EINVAL;

	if (cmd->stop_src == TRIG_EXT && cmd->scan_begin_src == TRIG_EXT)
		err |= -EINVAL;

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	switch (cmd->start_src) {
	case TRIG_NOW:
	case TRIG_EXT:
		err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
		break;
	case TRIG_INT:
		/* start_arg is the internal trigger (any value) */
		break;
	}

	if (cmd->scan_begin_src & (TRIG_FOLLOW | TRIG_EXT))
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);

	if ((cmd->scan_begin_src == TRIG_TIMER) &&
	    (cmd->convert_src == TRIG_TIMER) && (cmd->scan_end_arg == 1)) {
		cmd->scan_begin_src = TRIG_FOLLOW;
		cmd->convert_arg = cmd->scan_begin_arg;
		cmd->scan_begin_arg = 0;
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    devpriv->ai_ns_min);
	}

	if (cmd->scan_begin_src == TRIG_EXT) {
		if (cmd->scan_begin_arg) {
			cmd->scan_begin_arg = 0;
			err |= -EINVAL;
			err |= comedi_check_trigger_arg_max(&cmd->scan_end_arg,
							    65535);
		}
	}

	if (cmd->convert_src & (TRIG_TIMER | TRIG_NOW)) {
		err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
						    devpriv->ai_ns_min);
	}

	if (cmd->convert_src == TRIG_EXT)
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);

	err |= comedi_check_trigger_arg_min(&cmd->scan_end_arg,
					    cmd->chanlist_len);

	if ((cmd->scan_end_arg % cmd->chanlist_len)) {
		cmd->scan_end_arg =
		    cmd->chanlist_len * (cmd->scan_end_arg / cmd->chanlist_len);
		err |= -EINVAL;
	}

	if (err)
		return 3;

	/* step 4: fix up any arguments */

	if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->scan_begin_arg;
		comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	if (cmd->convert_src & (TRIG_TIMER | TRIG_NOW)) {
		arg = cmd->convert_arg;
		comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

		if (cmd->scan_begin_src == TRIG_TIMER &&
		    cmd->convert_src == TRIG_NOW) {
			if (cmd->convert_arg == 0) {
				arg = devpriv->ai_ns_min *
				      (cmd->scan_end_arg + 2);
			} else {
				arg = cmd->convert_arg * cmd->chanlist_len;
			}
			err |= comedi_check_trigger_arg_min(
				&cmd->scan_begin_arg, arg);
		}
	}

	if (err)
		return 4;

	/* Step 5: check channel list if it exists */

	if (cmd->chanlist)
		err |= pci9118_ai_check_chanlist(dev, s, cmd);

	if (err)
		return 5;

	return 0;
}