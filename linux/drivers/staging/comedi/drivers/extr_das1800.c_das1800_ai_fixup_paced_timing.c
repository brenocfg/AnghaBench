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
struct comedi_cmd {unsigned int convert_arg; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_8254_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 
 int comedi_check_trigger_arg_is (unsigned int*,unsigned int) ; 

__attribute__((used)) static int das1800_ai_fixup_paced_timing(struct comedi_device *dev,
					 struct comedi_cmd *cmd)
{
	unsigned int arg = cmd->convert_arg;

	/*
	 * Paced mode:
	 *	scan_begin_src is TRIG_FOLLOW
	 *	convert_src is TRIG_TIMER
	 *
	 * The convert_arg sets the pacer sample acquisition time.
	 * The max acquisition speed is limited to the boards
	 * 'ai_speed' (this was already verified). The min speed is
	 * limited by the cascaded 8254 timer.
	 */
	comedi_8254_cascade_ns_to_timer(dev->pacer, &arg, cmd->flags);
	return comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
}