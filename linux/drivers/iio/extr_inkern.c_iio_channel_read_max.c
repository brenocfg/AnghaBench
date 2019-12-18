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
typedef  enum iio_chan_info_enum { ____Placeholder_iio_chan_info_enum } iio_chan_info_enum ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_AVAIL_LIST 130 
#define  IIO_AVAIL_RANGE 129 
#define  IIO_VAL_INT 128 
 int iio_channel_read_avail (struct iio_channel*,int const**,int*,int*,int) ; 

__attribute__((used)) static int iio_channel_read_max(struct iio_channel *chan,
				int *val, int *val2, int *type,
				enum iio_chan_info_enum info)
{
	int unused;
	const int *vals;
	int length;
	int ret;

	if (!val2)
		val2 = &unused;

	ret = iio_channel_read_avail(chan, &vals, type, &length, info);
	switch (ret) {
	case IIO_AVAIL_RANGE:
		switch (*type) {
		case IIO_VAL_INT:
			*val = vals[2];
			break;
		default:
			*val = vals[4];
			*val2 = vals[5];
		}
		return 0;

	case IIO_AVAIL_LIST:
		if (length <= 0)
			return -EINVAL;
		switch (*type) {
		case IIO_VAL_INT:
			*val = vals[--length];
			while (length) {
				if (vals[--length] > *val)
					*val = vals[length];
			}
			break;
		default:
			/* FIXME: learn about max for other iio values */
			return -EINVAL;
		}
		return 0;

	default:
		return ret;
	}
}