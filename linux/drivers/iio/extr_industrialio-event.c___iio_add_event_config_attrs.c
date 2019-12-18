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
struct iio_dev {int num_channels; int /*<<< orphan*/ * channels; } ;

/* Variables and functions */
 int iio_device_add_event_sysfs (struct iio_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __iio_add_event_config_attrs(struct iio_dev *indio_dev)
{
	int j, ret, attrcount = 0;

	/* Dynamically created from the channels array */
	for (j = 0; j < indio_dev->num_channels; j++) {
		ret = iio_device_add_event_sysfs(indio_dev,
						 &indio_dev->channels[j]);
		if (ret < 0)
			return ret;
		attrcount += ret;
	}
	return attrcount;
}