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
struct comedi_cmd {int /*<<< orphan*/  stop_arg; int /*<<< orphan*/  chanlist_len; int /*<<< orphan*/  scan_end_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  start_arg; int /*<<< orphan*/  stop_src; int /*<<< orphan*/  scan_end_src; int /*<<< orphan*/  convert_src; int /*<<< orphan*/  scan_begin_src; int /*<<< orphan*/  start_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRIG_COUNT ; 
 int /*<<< orphan*/  TRIG_EXT ; 
 int /*<<< orphan*/  TRIG_FOLLOW ; 
 int /*<<< orphan*/  TRIG_NONE ; 
 int /*<<< orphan*/  TRIG_NOW ; 
 int comedi_check_trigger_arg_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_src (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parport_intr_cmdtest(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_cmd *cmd)
{
	int err = 0;

	/* Step 1 : check if triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_EXT);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_FOLLOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_NONE);

	if (err)
		return 1;

	/* Step 2a : make sure trigger sources are unique */
	/* Step 2b : and mutually compatible */

	/* Step 3: check if arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	if (err)
		return 3;

	/* Step 4: fix up any arguments */

	/* Step 5: check channel list if it exists */

	return 0;
}