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
struct jr3_pci_subdev_private {int /*<<< orphan*/  serial_no; } ;
struct comedi_subdevice {int /*<<< orphan*/  index; struct jr3_pci_subdev_private* private; } ;
struct comedi_device {int n_subdevices; int /*<<< orphan*/  class_dev; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jr3_pci_open(struct comedi_device *dev)
{
	struct jr3_pci_subdev_private *spriv;
	struct comedi_subdevice *s;
	int i;

	for (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		spriv = s->private;
		dev_dbg(dev->class_dev, "serial[%d]: %d\n", s->index,
			spriv->serial_no);
	}
	return 0;
}