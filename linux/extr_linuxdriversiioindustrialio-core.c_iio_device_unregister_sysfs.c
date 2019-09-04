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
struct TYPE_2__ {int /*<<< orphan*/ * attrs; } ;
struct iio_dev {TYPE_1__ chan_attr_group; int /*<<< orphan*/  channel_attr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_free_chan_devattr_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_device_unregister_sysfs(struct iio_dev *indio_dev)
{

	iio_free_chan_devattr_list(&indio_dev->channel_attr_list);
	kfree(indio_dev->chan_attr_group.attrs);
	indio_dev->chan_attr_group.attrs = NULL;
}