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
struct dpot_dac {int /*<<< orphan*/  dpot; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 struct dpot_dac* iio_priv (struct iio_dev*) ; 
 int iio_read_avail_channel_raw (int /*<<< orphan*/ ,int const**,int*) ; 

__attribute__((used)) static int dpot_dac_read_avail(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       const int **vals, int *type, int *length,
			       long mask)
{
	struct dpot_dac *dac = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		*type = IIO_VAL_INT;
		return iio_read_avail_channel_raw(dac->dpot, vals, length);
	}

	return -EINVAL;
}