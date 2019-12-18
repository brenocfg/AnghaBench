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
struct iio_dev {int modes; int num_channels; int /*<<< orphan*/  dev; struct iio_chan_spec* channels; } ;
struct iio_chan_spec {scalar_t__ scan_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int INDIO_ALL_BUFFER_MODES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static int iio_check_unique_scan_index(struct iio_dev *indio_dev)
{
	int i, j;
	const struct iio_chan_spec *channels = indio_dev->channels;

	if (!(indio_dev->modes & INDIO_ALL_BUFFER_MODES))
		return 0;

	for (i = 0; i < indio_dev->num_channels - 1; i++) {
		if (channels[i].scan_index < 0)
			continue;
		for (j = i + 1; j < indio_dev->num_channels; j++)
			if (channels[i].scan_index == channels[j].scan_index) {
				dev_err(&indio_dev->dev,
					"Duplicate scan index %d\n",
					channels[i].scan_index);
				return -EINVAL;
			}
	}

	return 0;
}