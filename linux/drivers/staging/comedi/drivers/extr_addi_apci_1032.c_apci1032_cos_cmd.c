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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  class_dev; struct apci1032_private* private; } ;
struct apci1032_private {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  mode2; int /*<<< orphan*/  mode1; } ;

/* Variables and functions */
 scalar_t__ APCI1032_CTRL_REG ; 
 scalar_t__ APCI1032_MODE1_REG ; 
 scalar_t__ APCI1032_MODE2_REG ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int apci1032_cos_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct apci1032_private *devpriv = dev->private;

	if (!devpriv->ctrl) {
		dev_warn(dev->class_dev,
			 "Interrupts disabled due to mode configuration!\n");
		return -EINVAL;
	}

	outl(devpriv->mode1, dev->iobase + APCI1032_MODE1_REG);
	outl(devpriv->mode2, dev->iobase + APCI1032_MODE2_REG);
	outl(devpriv->ctrl, dev->iobase + APCI1032_CTRL_REG);

	return 0;
}