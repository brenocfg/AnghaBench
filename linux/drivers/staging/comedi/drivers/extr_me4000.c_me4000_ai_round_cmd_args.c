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
struct me4000_private {int ai_init_ticks; int ai_scan_ticks; int ai_chan_ticks; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct me4000_private* private; } ;
struct comedi_cmd {int start_arg; int flags; int scan_begin_arg; int convert_arg; } ;

/* Variables and functions */
 int CMDF_ROUND_MASK ; 
 int CMDF_ROUND_NEAREST ; 
 int CMDF_ROUND_UP ; 

__attribute__((used)) static void me4000_ai_round_cmd_args(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_cmd *cmd)
{
	struct me4000_private *devpriv = dev->private;
	int rest;

	devpriv->ai_init_ticks = 0;
	devpriv->ai_scan_ticks = 0;
	devpriv->ai_chan_ticks = 0;

	if (cmd->start_arg) {
		devpriv->ai_init_ticks = (cmd->start_arg * 33) / 1000;
		rest = (cmd->start_arg * 33) % 1000;

		if ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_NEAREST) {
			if (rest > 33)
				devpriv->ai_init_ticks++;
		} else if ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_UP) {
			if (rest)
				devpriv->ai_init_ticks++;
		}
	}

	if (cmd->scan_begin_arg) {
		devpriv->ai_scan_ticks = (cmd->scan_begin_arg * 33) / 1000;
		rest = (cmd->scan_begin_arg * 33) % 1000;

		if ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_NEAREST) {
			if (rest > 33)
				devpriv->ai_scan_ticks++;
		} else if ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_UP) {
			if (rest)
				devpriv->ai_scan_ticks++;
		}
	}

	if (cmd->convert_arg) {
		devpriv->ai_chan_ticks = (cmd->convert_arg * 33) / 1000;
		rest = (cmd->convert_arg * 33) % 1000;

		if ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_NEAREST) {
			if (rest > 33)
				devpriv->ai_chan_ticks++;
		} else if ((cmd->flags & CMDF_ROUND_MASK) == CMDF_ROUND_UP) {
			if (rest)
				devpriv->ai_chan_ticks++;
		}
	}
}