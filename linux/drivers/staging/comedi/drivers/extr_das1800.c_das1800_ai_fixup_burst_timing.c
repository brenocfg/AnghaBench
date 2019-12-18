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
struct comedi_device {int /*<<< orphan*/  pacer; } ;
struct comedi_cmd {unsigned int convert_arg; int flags; scalar_t__ scan_begin_src; unsigned int chanlist_len; unsigned int scan_begin_arg; } ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 
 int comedi_check_trigger_arg_max (unsigned int*,int) ; 
 int comedi_check_trigger_arg_min (unsigned int*,unsigned int) ; 

__attribute__((used)) static int das1800_ai_fixup_burst_timing(struct comedi_device *dev,
					 struct comedi_cmd *cmd)
{
	unsigned int arg = cmd->convert_arg;
	int err = 0;

	/*
	 * Burst mode:
	 *	scan_begin_src is TRIG_TIMER or TRIG_EXT
	 *	convert_src is TRIG_TIMER
	 *
	 * The convert_arg sets burst sample acquisition time.
	 * The max acquisition speed is limited to the boards
	 * 'ai_speed' (this was already verified). The min speed is
	 * limiited to 64 microseconds,
	 */
	err |= comedi_check_trigger_arg_max(&arg, 64000);

	/* round to microseconds then verify */
	switch (cmd->flags & CMDF_ROUND_MASK) {
	case CMDF_ROUND_NEAREST:
	default:
		arg = DIV_ROUND_CLOSEST(arg, 1000);
		break;
	case CMDF_ROUND_DOWN:
		arg = arg / 1000;
		break;
	case CMDF_ROUND_UP:
		arg = DIV_ROUND_UP(arg, 1000);
		break;
	}
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg * 1000);

	/*
	 * The pacer can be used to set the scan sample rate. The max scan
	 * speed is limited by the conversion speed and the number of channels
	 * to convert. The min speed is limited by the cascaded 8254 timer.
	 */
	if (cmd->scan_begin_src == TRIG_TIMER) {
		arg = cmd->convert_arg * cmd->chanlist_len;
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg, arg);

		arg = cmd->scan_begin_arg;
		comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	}

	return err;
}