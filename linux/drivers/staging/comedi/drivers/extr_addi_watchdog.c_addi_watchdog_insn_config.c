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
struct comedi_subdevice {unsigned int maxdata; struct addi_watchdog_private* private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct addi_watchdog_private {unsigned int wdog_ctrl; scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int ADDI_TCW_CTRL_ENA ; 
 scalar_t__ ADDI_TCW_CTRL_REG ; 
 scalar_t__ ADDI_TCW_RELOAD_REG ; 
 int EINVAL ; 
#define  INSN_CONFIG_ARM 129 
#define  INSN_CONFIG_DISARM 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static int addi_watchdog_insn_config(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	struct addi_watchdog_private *spriv = s->private;
	unsigned int reload;

	switch (data[0]) {
	case INSN_CONFIG_ARM:
		spriv->wdog_ctrl = ADDI_TCW_CTRL_ENA;
		reload = data[1] & s->maxdata;
		outl(reload, spriv->iobase + ADDI_TCW_RELOAD_REG);

		/* Time base is 20ms, let the user know the timeout */
		dev_info(dev->class_dev, "watchdog enabled, timeout:%dms\n",
			 20 * reload + 20);
		break;
	case INSN_CONFIG_DISARM:
		spriv->wdog_ctrl = 0;
		break;
	default:
		return -EINVAL;
	}

	outl(spriv->wdog_ctrl, spriv->iobase + ADDI_TCW_CTRL_REG);

	return insn->n;
}