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
struct usbduxsigma_private {int* dux_commands; int /*<<< orphan*/  mut; scalar_t__ ao_cmd_running; } ;
struct comedi_subdevice {unsigned int* readback; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  USBDUXSIGMA_DA_CMD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usbbuxsigma_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsigma_ao_insn_write(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	struct usbduxsigma_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	int ret;
	int i;

	mutex_lock(&devpriv->mut);
	if (devpriv->ao_cmd_running) {
		mutex_unlock(&devpriv->mut);
		return -EBUSY;
	}

	for (i = 0; i < insn->n; i++) {
		devpriv->dux_commands[1] = 1;		/* num channels */
		devpriv->dux_commands[2] = data[i];	/* value */
		devpriv->dux_commands[3] = chan;	/* channel number */
		ret = usbbuxsigma_send_cmd(dev, USBDUXSIGMA_DA_CMD);
		if (ret < 0) {
			mutex_unlock(&devpriv->mut);
			return ret;
		}
		s->readback[chan] = data[i];
	}
	mutex_unlock(&devpriv->mut);

	return insn->n;
}