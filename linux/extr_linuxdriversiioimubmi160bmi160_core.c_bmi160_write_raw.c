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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct bmi160_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int bmi160_set_odr (struct bmi160_data*,int /*<<< orphan*/ ,int,int) ; 
 int bmi160_set_scale (struct bmi160_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bmi160_to_sensor (int /*<<< orphan*/ ) ; 
 struct bmi160_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int bmi160_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct bmi160_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		return bmi160_set_scale(data,
					bmi160_to_sensor(chan->type), val2);
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		return bmi160_set_odr(data, bmi160_to_sensor(chan->type),
				      val, val2);
	default:
		return -EINVAL;
	}

	return 0;
}