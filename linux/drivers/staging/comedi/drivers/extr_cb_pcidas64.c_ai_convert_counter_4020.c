#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_2__ {unsigned int divisor; } ;
struct pcidas64_private {TYPE_1__ ext_clock; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct pcidas64_private* private; } ;
struct comedi_cmd {int scan_begin_src; unsigned int scan_begin_arg; } ;

/* Variables and functions */
 unsigned int TIMER_BASE ; 
#define  TRIG_OTHER 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u32 ai_convert_counter_4020(struct comedi_device *dev,
				   struct comedi_cmd *cmd)
{
	struct pcidas64_private *devpriv = dev->private;
	unsigned int divisor;

	switch (cmd->scan_begin_src) {
	case TRIG_TIMER:
		divisor = cmd->scan_begin_arg / TIMER_BASE;
		break;
	case TRIG_OTHER:
		divisor = devpriv->ext_clock.divisor;
		break;
	default:		/* should never happen */
		dev_err(dev->class_dev, "bug! failed to set ai pacing!\n");
		divisor = 1000;
		break;
	}

	/* supposed to load counter with desired divisor minus 2 for 4020 */
	return divisor - 2;
}