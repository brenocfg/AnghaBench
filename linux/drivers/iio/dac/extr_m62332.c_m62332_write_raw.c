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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int m62332_set_value (struct iio_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m62332_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int val, int val2,
			    long mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val < 0 || val > 255)
			return -EINVAL;

		return m62332_set_value(indio_dev, val, chan->channel);
	default:
		break;
	}

	return -EINVAL;
}