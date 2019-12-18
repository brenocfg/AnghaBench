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
struct iio_dev {int /*<<< orphan*/  groupcounter; int /*<<< orphan*/ ** groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_trigger_consumer_attr_group ; 

void iio_device_register_trigger_consumer(struct iio_dev *indio_dev)
{
	indio_dev->groups[indio_dev->groupcounter++] =
		&iio_trigger_consumer_attr_group;
}