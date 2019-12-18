#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {struct comedi_file* private_data; } ;
struct comedi_subdevice {int subdev_flags; TYPE_2__* async; struct file* busy; } ;
struct comedi_file {int /*<<< orphan*/  write_subdev; } ;
struct comedi_device {unsigned long n_subdevices; struct comedi_subdevice* subdevices; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int CMDF_WRITE ; 
 int EBUSY ; 
 int EINVAL ; 
 int SDF_CMD_WRITE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct comedi_subdevice*) ; 
 struct comedi_subdevice* comedi_file_write_subdevice (struct file*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_setwsubd_ioctl(struct comedi_device *dev, unsigned long arg,
			     struct file *file)
{
	struct comedi_file *cfp = file->private_data;
	struct comedi_subdevice *s_old, *s_new;

	lockdep_assert_held(&dev->mutex);
	if (arg >= dev->n_subdevices)
		return -EINVAL;

	s_new = &dev->subdevices[arg];
	s_old = comedi_file_write_subdevice(file);
	if (s_old == s_new)
		return 0;	/* no change */

	if (!(s_new->subdev_flags & SDF_CMD_WRITE))
		return -EINVAL;

	/*
	 * Check the file isn't still busy handling a "write" command on the
	 * old subdevice (if any).
	 */
	if (s_old && s_old->busy == file && s_old->async &&
	    (s_old->async->cmd.flags & CMDF_WRITE))
		return -EBUSY;

	WRITE_ONCE(cfp->write_subdev, s_new);
	return 0;
}