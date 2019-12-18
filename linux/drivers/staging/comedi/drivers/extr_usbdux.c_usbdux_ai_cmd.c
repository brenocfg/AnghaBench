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
struct usbdux_private {int ai_cmd_running; int* dux_commands; int ai_interval; int ai_timer; int ai_counter; int /*<<< orphan*/  mut; int /*<<< orphan*/  n_ai_urbs; int /*<<< orphan*/  ai_urbs; scalar_t__ high_speed; } ;
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {struct usbdux_private* private; } ;
struct comedi_cmd {int chanlist_len; int scan_begin_arg; scalar_t__ start_src; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ TRIG_NOW ; 
 int /*<<< orphan*/  USBDUX_CMD_MULT_AI ; 
 int create_adc_command (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_dux_commands (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usbdux_ai_inttrig ; 
 int usbdux_submit_urbs (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbdux_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct usbdux_private *devpriv = dev->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int len = cmd->chanlist_len;
	int ret = -EBUSY;
	int i;

	/* block other CPUs from starting an ai_cmd */
	mutex_lock(&devpriv->mut);

	if (devpriv->ai_cmd_running)
		goto ai_cmd_exit;

	devpriv->dux_commands[1] = len;
	for (i = 0; i < len; ++i) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int range = CR_RANGE(cmd->chanlist[i]);

		devpriv->dux_commands[i + 2] = create_adc_command(chan, range);
	}

	ret = send_dux_commands(dev, USBDUX_CMD_MULT_AI);
	if (ret < 0)
		goto ai_cmd_exit;

	if (devpriv->high_speed) {
		/*
		 * every channel gets a time window of 125us. Thus, if we
		 * sample all 8 channels we need 1ms. If we sample only one
		 * channel we need only 125us
		 */
		devpriv->ai_interval = 1;
		/* find a power of 2 for the interval */
		while (devpriv->ai_interval < len)
			devpriv->ai_interval *= 2;

		devpriv->ai_timer = cmd->scan_begin_arg /
				    (125000 * devpriv->ai_interval);
	} else {
		/* interval always 1ms */
		devpriv->ai_interval = 1;
		devpriv->ai_timer = cmd->scan_begin_arg / 1000000;
	}
	if (devpriv->ai_timer < 1) {
		ret = -EINVAL;
		goto ai_cmd_exit;
	}

	devpriv->ai_counter = devpriv->ai_timer;

	if (cmd->start_src == TRIG_NOW) {
		/* enable this acquisition operation */
		devpriv->ai_cmd_running = 1;
		ret = usbdux_submit_urbs(dev, devpriv->ai_urbs,
					 devpriv->n_ai_urbs, 1);
		if (ret < 0) {
			devpriv->ai_cmd_running = 0;
			/* fixme: unlink here?? */
			goto ai_cmd_exit;
		}
		s->async->inttrig = NULL;
	} else {
		/* TRIG_INT */
		/* don't enable the acquision operation */
		/* wait for an internal signal */
		s->async->inttrig = usbdux_ai_inttrig;
	}

ai_cmd_exit:
	mutex_unlock(&devpriv->mut);

	return ret;
}