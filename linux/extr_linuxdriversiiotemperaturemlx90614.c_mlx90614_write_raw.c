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
struct mlx90614_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBEMISSIVITY 129 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 128 
 int MLX90614_CONST_EMISSIVITY_RESOLUTION ; 
 int MLX90614_CONST_RAW_EMISSIVITY_MAX ; 
 int /*<<< orphan*/  MLX90614_EMISSIVITY ; 
 struct mlx90614_data* iio_priv (struct iio_dev*) ; 
 int mlx90614_iir_search (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx90614_power_get (struct mlx90614_data*,int) ; 
 int /*<<< orphan*/  mlx90614_power_put (struct mlx90614_data*) ; 
 int mlx90614_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx90614_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *channel, int val,
			     int val2, long mask)
{
	struct mlx90614_data *data = iio_priv(indio_dev);
	s32 ret;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBEMISSIVITY: /* 1/65535 / LSB */
		if (val < 0 || val2 < 0 || val > 1 || (val == 1 && val2 != 0))
			return -EINVAL;
		val = val * MLX90614_CONST_RAW_EMISSIVITY_MAX +
			val2 / MLX90614_CONST_EMISSIVITY_RESOLUTION;

		mlx90614_power_get(data, false);
		mutex_lock(&data->lock);
		ret = mlx90614_write_word(data->client, MLX90614_EMISSIVITY,
					  val);
		mutex_unlock(&data->lock);
		mlx90614_power_put(data);

		return ret;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY: /* IIR Filter setting */
		if (val < 0 || val2 < 0)
			return -EINVAL;

		mlx90614_power_get(data, false);
		mutex_lock(&data->lock);
		ret = mlx90614_iir_search(data->client,
					  val * 100 + val2 / 10000);
		mutex_unlock(&data->lock);
		mlx90614_power_put(data);

		return ret;
	default:
		return -EINVAL;
	}
}