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
struct cros_ec_sensors_core_state {int /*<<< orphan*/  frequencies; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int IIO_AVAIL_LIST ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int IIO_VAL_INT ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 

int cros_ec_sensors_core_read_avail(struct iio_dev *indio_dev,
				    struct iio_chan_spec const *chan,
				    const int **vals,
				    int *type,
				    int *length,
				    long mask)
{
	struct cros_ec_sensors_core_state *state = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		*length = ARRAY_SIZE(state->frequencies);
		*vals = (const int *)&state->frequencies;
		*type = IIO_VAL_INT;
		return IIO_AVAIL_LIST;
	}

	return -EINVAL;
}