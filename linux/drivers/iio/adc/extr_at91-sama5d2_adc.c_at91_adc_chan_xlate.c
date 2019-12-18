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
struct TYPE_2__ {int scan_index; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int at91_adc_chan_xlate(struct iio_dev *indio_dev, int chan)
{
	int i;

	for (i = 0; i < indio_dev->num_channels; i++) {
		if (indio_dev->channels[i].scan_index == chan)
			return i;
	}
	return -EINVAL;
}