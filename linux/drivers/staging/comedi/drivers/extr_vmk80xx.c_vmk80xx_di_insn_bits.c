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
struct vmk80xx_private {unsigned char* usb_rx_buf; scalar_t__ model; int /*<<< orphan*/  limit_sem; int /*<<< orphan*/ * usb_tx_buf; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int VMK8055_DI_REG ; 
 scalar_t__ VMK8055_MODEL ; 
 int /*<<< orphan*/  VMK8061_CMD_RD_DI ; 
 int VMK8061_DI_REG ; 
 scalar_t__ VMK8061_MODEL ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int vmk80xx_read_packet (struct comedi_device*) ; 

__attribute__((used)) static int vmk80xx_di_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	unsigned char *rx_buf;
	int reg;
	int retval;

	down(&devpriv->limit_sem);

	rx_buf = devpriv->usb_rx_buf;

	if (devpriv->model == VMK8061_MODEL) {
		reg = VMK8061_DI_REG;
		devpriv->usb_tx_buf[0] = VMK8061_CMD_RD_DI;
	} else {
		reg = VMK8055_DI_REG;
	}

	retval = vmk80xx_read_packet(dev);

	if (!retval) {
		if (devpriv->model == VMK8055_MODEL)
			data[1] = (((rx_buf[reg] >> 4) & 0x03) |
				  ((rx_buf[reg] << 2) & 0x04) |
				  ((rx_buf[reg] >> 3) & 0x18));
		else
			data[1] = rx_buf[reg];

		retval = 2;
	}

	up(&devpriv->limit_sem);

	return retval;
}