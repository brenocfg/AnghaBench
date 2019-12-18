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
struct vmk80xx_private {int* usb_tx_buf; int /*<<< orphan*/  limit_sem; int /*<<< orphan*/  model; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_RESET 128 
 int VMK8055_CMD_RST_CNT1 ; 
 int VMK8055_CMD_RST_CNT2 ; 
 int VMK8055_CNT1_REG ; 
 int VMK8055_CNT2_REG ; 
 int /*<<< orphan*/  VMK8055_MODEL ; 
 int VMK8061_CMD_RST_CNT ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int vmk80xx_write_packet (struct comedi_device*,int) ; 

__attribute__((used)) static int vmk80xx_cnt_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct vmk80xx_private *devpriv = dev->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	int cmd;
	int reg;
	int ret;

	down(&devpriv->limit_sem);
	switch (data[0]) {
	case INSN_CONFIG_RESET:
		if (devpriv->model == VMK8055_MODEL) {
			if (!chan) {
				cmd = VMK8055_CMD_RST_CNT1;
				reg = VMK8055_CNT1_REG;
			} else {
				cmd = VMK8055_CMD_RST_CNT2;
				reg = VMK8055_CNT2_REG;
			}
			devpriv->usb_tx_buf[reg] = 0x00;
		} else {
			cmd = VMK8061_CMD_RST_CNT;
		}
		ret = vmk80xx_write_packet(dev, cmd);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	up(&devpriv->limit_sem);

	return ret ? ret : insn->n;
}