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
struct comedi_device {int attached; int /*<<< orphan*/  attach_lock; TYPE_1__* driver; int /*<<< orphan*/  detach_count; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct comedi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_device_cancel_all (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_device_detach_cleanup (struct comedi_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void comedi_device_detach(struct comedi_device *dev)
{
	lockdep_assert_held(&dev->mutex);
	comedi_device_cancel_all(dev);
	down_write(&dev->attach_lock);
	dev->attached = false;
	dev->detach_count++;
	if (dev->driver)
		dev->driver->detach(dev);
	comedi_device_detach_cleanup(dev);
	up_write(&dev->attach_lock);
}