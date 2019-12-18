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
struct iio_dev {TYPE_2__* event_interface; } ;
struct TYPE_3__ {TYPE_2__* attrs; } ;
struct TYPE_4__ {TYPE_1__ group; int /*<<< orphan*/  dev_attr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_free_chan_devattr_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

void iio_device_unregister_eventset(struct iio_dev *indio_dev)
{
	if (indio_dev->event_interface == NULL)
		return;
	iio_free_chan_devattr_list(&indio_dev->event_interface->dev_attr_list);
	kfree(indio_dev->event_interface->group.attrs);
	kfree(indio_dev->event_interface);
}