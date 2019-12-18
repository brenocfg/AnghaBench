#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  devt; } ;
struct comedi_subdevice {int subdev_flags; TYPE_1__* async; } ;
struct comedi_device {int /*<<< orphan*/  mutex; } ;
typedef  int ssize_t ;
struct TYPE_2__ {unsigned int max_bufsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 int SDF_CMD_WRITE ; 
 int UINT_MAX ; 
 struct comedi_device* comedi_dev_get_from_minor (unsigned int) ; 
 int /*<<< orphan*/  comedi_dev_put (struct comedi_device*) ; 
 struct comedi_subdevice* comedi_write_subdevice (struct comedi_device*,unsigned int) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t max_write_buffer_kb_store(struct device *csdev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	unsigned int minor = MINOR(csdev->devt);
	struct comedi_device *dev;
	struct comedi_subdevice *s;
	unsigned int size;
	int err;

	err = kstrtouint(buf, 10, &size);
	if (err)
		return err;
	if (size > (UINT_MAX / 1024))
		return -EINVAL;
	size *= 1024;

	dev = comedi_dev_get_from_minor(minor);
	if (!dev)
		return -ENODEV;

	mutex_lock(&dev->mutex);
	s = comedi_write_subdevice(dev, minor);
	if (s && (s->subdev_flags & SDF_CMD_WRITE) && s->async)
		s->async->max_bufsize = size;
	else
		err = -EINVAL;
	mutex_unlock(&dev->mutex);

	comedi_dev_put(dev);
	return err ? err : count;
}