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
struct comedi_device {int attached; int /*<<< orphan*/  attach_lock; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int __comedi_device_postconfig (struct comedi_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int comedi_device_postconfig(struct comedi_device *dev)
{
	int ret;

	lockdep_assert_held(&dev->mutex);
	ret = __comedi_device_postconfig(dev);
	if (ret < 0)
		return ret;
	down_write(&dev->attach_lock);
	dev->attached = true;
	up_write(&dev->attach_lock);
	return 0;
}