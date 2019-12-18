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
struct vmk80xx_private {unsigned char* usb_rx_buf; unsigned char* usb_tx_buf; scalar_t__ model; int /*<<< orphan*/  limit_sem; } ;
struct comedi_subdevice {unsigned char state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int VMK8055_CMD_WRT_AD ; 
 int VMK8055_DO_REG ; 
 int VMK8061_CMD_DO ; 
 unsigned char VMK8061_CMD_RD_DO ; 
 int VMK8061_DO_REG ; 
 scalar_t__ VMK8061_MODEL ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int vmk80xx_read_packet (struct comedi_device*) ; 
 int vmk80xx_write_packet (struct comedi_device*,int) ; 

__attribute__((used)) static int vmk80xx_do_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn,
				unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	unsigned char *rx_buf = devpriv->usb_rx_buf;
	unsigned char *tx_buf = devpriv->usb_tx_buf;
	int reg, cmd;
	int ret = 0;

	if (devpriv->model == VMK8061_MODEL) {
		reg = VMK8061_DO_REG;
		cmd = VMK8061_CMD_DO;
	} else { /* VMK8055_MODEL */
		reg = VMK8055_DO_REG;
		cmd = VMK8055_CMD_WRT_AD;
	}

	down(&devpriv->limit_sem);

	if (comedi_dio_update_state(s, data)) {
		tx_buf[reg] = s->state;
		ret = vmk80xx_write_packet(dev, cmd);
		if (ret)
			goto out;
	}

	if (devpriv->model == VMK8061_MODEL) {
		tx_buf[0] = VMK8061_CMD_RD_DO;
		ret = vmk80xx_read_packet(dev);
		if (ret)
			goto out;
		data[1] = rx_buf[reg];
	} else {
		data[1] = s->state;
	}

out:
	up(&devpriv->limit_sem);

	return ret ? ret : insn->n;
}