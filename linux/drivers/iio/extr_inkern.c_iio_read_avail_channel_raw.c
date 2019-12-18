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
struct iio_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_RAW ; 
 int IIO_VAL_INT ; 
 int iio_read_avail_channel_attribute (struct iio_channel*,int const**,int*,int*,int /*<<< orphan*/ ) ; 

int iio_read_avail_channel_raw(struct iio_channel *chan,
			       const int **vals, int *length)
{
	int ret;
	int type;

	ret = iio_read_avail_channel_attribute(chan, vals, &type, length,
					 IIO_CHAN_INFO_RAW);

	if (ret >= 0 && type != IIO_VAL_INT)
		/* raw values are assumed to be IIO_VAL_INT */
		ret = -EINVAL;

	return ret;
}