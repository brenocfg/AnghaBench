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
struct comedi_subdevice {int subdev_flags; } ;
struct comedi_device {struct comedi_subdevice* read_subdev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 int SDF_CMD_READ ; 
 struct comedi_subdevice* comedi_subdevice_from_minor (struct comedi_device const*,unsigned int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct comedi_subdevice *
comedi_read_subdevice(const struct comedi_device *dev, unsigned int minor)
{
	struct comedi_subdevice *s;

	lockdep_assert_held(&dev->mutex);
	if (minor >= COMEDI_NUM_BOARD_MINORS) {
		s = comedi_subdevice_from_minor(dev, minor);
		if (!s || (s->subdev_flags & SDF_CMD_READ))
			return s;
	}
	return dev->read_subdev;
}