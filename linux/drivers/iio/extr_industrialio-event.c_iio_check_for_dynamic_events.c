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
struct iio_dev {int num_channels; TYPE_1__* channels; } ;
struct TYPE_2__ {scalar_t__ num_event_specs; } ;

/* Variables and functions */

__attribute__((used)) static bool iio_check_for_dynamic_events(struct iio_dev *indio_dev)
{
	int j;

	for (j = 0; j < indio_dev->num_channels; j++) {
		if (indio_dev->channels[j].num_event_specs != 0)
			return true;
	}
	return false;
}