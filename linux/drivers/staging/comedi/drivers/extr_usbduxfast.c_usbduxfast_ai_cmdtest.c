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
struct comedi_device {int dummy; } ;
struct comedi_cmd {int start_src; int scan_begin_src; int convert_src; int scan_end_src; int stop_src; int start_arg; int chanlist_len; int scan_end_arg; int convert_arg; unsigned int stop_arg; scalar_t__ chanlist; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_SAMPLING_PERIOD ; 
 int MIN_SAMPLING_PERIOD ; 
 int TRIG_COUNT ; 
 int TRIG_EXT ; 
 int TRIG_FOLLOW ; 
 int TRIG_INT ; 
 int TRIG_NONE ; 
 int TRIG_NOW ; 
 int TRIG_TIMER ; 
 int comedi_check_trigger_arg_is (int*,unsigned int) ; 
 int comedi_check_trigger_arg_max (unsigned int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_min (unsigned int*,int) ; 
 int comedi_check_trigger_is_unique (int) ; 
 int comedi_check_trigger_src (int*,int) ; 
 int usbduxfast_ai_check_chanlist (struct comedi_device*,struct comedi_subdevice*,struct comedi_cmd*) ; 

__attribute__((used)) static int usbduxfast_ai_cmdtest(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_cmd *cmd)
{
	int err = 0;
	unsigned int steps;
	unsigned int arg;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src,
					TRIG_NOW | TRIG_EXT | TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->start_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	if (err)
		return 2;

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	if (!cmd->chanlist_len)
		err |= -EINVAL;

	/* external start trigger is only valid for 1 or 16 channels */
	if (cmd->start_src == TRIG_EXT &&
	    cmd->chanlist_len != 1 && cmd->chanlist_len != 16)
		err |= -EINVAL;

	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	/*
	 * Validate the conversion timing:
	 * for 1 channel the timing in 30MHz "steps" is:
	 *	steps <= MAX_SAMPLING_PERIOD
	 * for all other chanlist_len it is:
	 *	MIN_SAMPLING_PERIOD <= steps <= MAX_SAMPLING_PERIOD
	 */
	steps = (cmd->convert_arg * 30) / 1000;
	if (cmd->chanlist_len !=  1)
		err |= comedi_check_trigger_arg_min(&steps,
						    MIN_SAMPLING_PERIOD);
	err |= comedi_check_trigger_arg_max(&steps, MAX_SAMPLING_PERIOD);
	arg = (steps * 1000) / 30;
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);

	if (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	else	/* TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list if it exists */
	if (cmd->chanlist && cmd->chanlist_len > 0)
		err |= usbduxfast_ai_check_chanlist(dev, s, cmd);
	if (err)
		return 5;

	return 0;
}