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
struct mlx90632_data {int emissivity; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBEMISSIVITY 128 
 struct mlx90632_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mlx90632_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *channel, int val,
			      int val2, long mask)
{
	struct mlx90632_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBEMISSIVITY:
		/* Confirm we are within 0 and 1.0 */
		if (val < 0 || val2 < 0 || val > 1 ||
		    (val == 1 && val2 != 0))
			return -EINVAL;
		data->emissivity = val * 1000 + val2 / 1000;
		return 0;
	default:
		return -EINVAL;
	}
}