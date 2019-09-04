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
struct iio_chan_spec {int dummy; } ;
struct as3935_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3935_DATA ; 
 int AS3935_DATA_MASK ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int as3935_read (struct as3935_state*,int /*<<< orphan*/ ,int*) ; 
 struct as3935_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int as3935_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val,
			   int *val2,
			   long m)
{
	struct as3935_state *st = iio_priv(indio_dev);
	int ret;


	switch (m) {
	case IIO_CHAN_INFO_PROCESSED:
	case IIO_CHAN_INFO_RAW:
		*val2 = 0;
		ret = as3935_read(st, AS3935_DATA, val);
		if (ret)
			return ret;

		/* storm out of range */
		if (*val == AS3935_DATA_MASK)
			return -EINVAL;

		if (m == IIO_CHAN_INFO_RAW)
			return IIO_VAL_INT;

		if (m == IIO_CHAN_INFO_PROCESSED)
			*val *= 1000;
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = 1000;
		break;
	default:
		return -EINVAL;
	}

	return IIO_VAL_INT;
}