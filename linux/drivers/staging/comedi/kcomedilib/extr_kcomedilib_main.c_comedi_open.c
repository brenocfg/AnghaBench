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
struct comedi_device {int /*<<< orphan*/  attach_lock; scalar_t__ attached; } ;

/* Variables and functions */
 unsigned int COMEDI_NUM_BOARD_MINORS ; 
 struct comedi_device* comedi_dev_get_from_minor (unsigned int) ; 
 int /*<<< orphan*/  comedi_dev_put (struct comedi_device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct comedi_device *comedi_open(const char *filename)
{
	struct comedi_device *dev, *retval = NULL;
	unsigned int minor;

	if (strncmp(filename, "/dev/comedi", 11) != 0)
		return NULL;

	if (kstrtouint(filename + 11, 0, &minor))
		return NULL;

	if (minor >= COMEDI_NUM_BOARD_MINORS)
		return NULL;

	dev = comedi_dev_get_from_minor(minor);
	if (!dev)
		return NULL;

	down_read(&dev->attach_lock);
	if (dev->attached)
		retval = dev;
	else
		retval = NULL;
	up_read(&dev->attach_lock);

	if (!retval)
		comedi_dev_put(dev);

	return retval;
}