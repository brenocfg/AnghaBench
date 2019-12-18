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
struct vmk80xx_private {unsigned int* usb_rx_buf; int /*<<< orphan*/  limit_sem; int /*<<< orphan*/ * usb_tx_buf; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int VMK8061_AO_REG ; 
 int /*<<< orphan*/  VMK8061_CMD_RD_AO ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 scalar_t__ vmk80xx_read_packet (struct comedi_device*) ; 

__attribute__((used)) static int vmk80xx_ao_insn_read(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	int chan;
	int reg;
	int n;

	down(&devpriv->limit_sem);
	chan = CR_CHAN(insn->chanspec);

	reg = VMK8061_AO_REG - 1;

	devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_AO;

	for (n = 0; n < insn->n; n++) {
		if (vmk80xx_read_packet(dev))
			break;

		data[n] = devpriv->usb_rx_buf[reg + chan];
	}

	up(&devpriv->limit_sem);

	return n;
}