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
struct ni_private {int ao_cmd2; scalar_t__ ao_needs_arming; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct ni_private* private; } ;
struct comedi_cmd {unsigned int start_arg; scalar_t__ start_src; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NISTC_AO_CMD2_REG ; 
 int NISTC_AO_CMD2_START1_PULSE ; 
 scalar_t__ TRIG_INT ; 
 int ni_ao_arm (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_ao_inttrig(struct comedi_device *dev,
			 struct comedi_subdevice *s,
			 unsigned int trig_num)
{
	struct ni_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int ret;

	/*
	 * Require trig_num == cmd->start_arg when cmd->start_src == TRIG_INT.
	 * For backwards compatibility, also allow trig_num == 0 when
	 * cmd->start_src != TRIG_INT (i.e. when cmd->start_src == TRIG_EXT);
	 * in that case, the internal trigger is being used as a pre-trigger
	 * before the external trigger.
	 */
	if (!(trig_num == cmd->start_arg ||
	      (trig_num == 0 && cmd->start_src != TRIG_INT)))
		return -EINVAL;

	/*
	 * Null trig at beginning prevent ao start trigger from executing more
	 * than once per command.
	 */
	s->async->inttrig = NULL;

	if (devpriv->ao_needs_arming) {
		/* only arm this device if it still needs arming */
		ret = ni_ao_arm(dev, s);
		if (ret)
			return ret;
	}

	ni_stc_writew(dev, NISTC_AO_CMD2_START1_PULSE | devpriv->ao_cmd2,
		      NISTC_AO_CMD2_REG);

	return 0;
}