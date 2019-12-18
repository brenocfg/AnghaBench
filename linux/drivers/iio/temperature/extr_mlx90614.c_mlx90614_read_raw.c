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
typedef  int /*<<< orphan*/  u8 ;
struct mlx90614_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; int /*<<< orphan*/  channel2; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  IIO_CHAN_INFO_CALIBEMISSIVITY 134 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 133 
#define  IIO_CHAN_INFO_OFFSET 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_MOD_TEMP_AMBIENT 129 
#define  IIO_MOD_TEMP_OBJECT 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/  MLX90614_CONFIG ; 
 int MLX90614_CONFIG_IIR_MASK ; 
 int MLX90614_CONST_EMISSIVITY_RESOLUTION ; 
 int MLX90614_CONST_OFFSET_DEC ; 
 int MLX90614_CONST_OFFSET_REM ; 
 int MLX90614_CONST_RAW_EMISSIVITY_MAX ; 
 int MLX90614_CONST_SCALE ; 
 int /*<<< orphan*/  MLX90614_EMISSIVITY ; 
 int /*<<< orphan*/  MLX90614_TA ; 
 int /*<<< orphan*/  MLX90614_TOBJ1 ; 
 int /*<<< orphan*/  MLX90614_TOBJ2 ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx90614_data* iio_priv (struct iio_dev*) ; 
 int* mlx90614_iir_values ; 
 int mlx90614_power_get (struct mlx90614_data*,int) ; 
 int /*<<< orphan*/  mlx90614_power_put (struct mlx90614_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx90614_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *channel, int *val,
			    int *val2, long mask)
{
	struct mlx90614_data *data = iio_priv(indio_dev);
	u8 cmd;
	s32 ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW: /* 0.02K / LSB */
		switch (channel->channel2) {
		case IIO_MOD_TEMP_AMBIENT:
			cmd = MLX90614_TA;
			break;
		case IIO_MOD_TEMP_OBJECT:
			switch (channel->channel) {
			case 0:
				cmd = MLX90614_TOBJ1;
				break;
			case 1:
				cmd = MLX90614_TOBJ2;
				break;
			default:
				return -EINVAL;
			}
			break;
		default:
			return -EINVAL;
		}

		ret = mlx90614_power_get(data, true);
		if (ret < 0)
			return ret;
		ret = i2c_smbus_read_word_data(data->client, cmd);
		mlx90614_power_put(data);

		if (ret < 0)
			return ret;

		/* MSB is an error flag */
		if (ret & 0x8000)
			return -EIO;

		*val = ret;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OFFSET:
		*val = MLX90614_CONST_OFFSET_DEC;
		*val2 = MLX90614_CONST_OFFSET_REM;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SCALE:
		*val = MLX90614_CONST_SCALE;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBEMISSIVITY: /* 1/65535 / LSB */
		mlx90614_power_get(data, false);
		mutex_lock(&data->lock);
		ret = i2c_smbus_read_word_data(data->client,
					       MLX90614_EMISSIVITY);
		mutex_unlock(&data->lock);
		mlx90614_power_put(data);

		if (ret < 0)
			return ret;

		if (ret == MLX90614_CONST_RAW_EMISSIVITY_MAX) {
			*val = 1;
			*val2 = 0;
		} else {
			*val = 0;
			*val2 = ret * MLX90614_CONST_EMISSIVITY_RESOLUTION;
		}
		return IIO_VAL_INT_PLUS_NANO;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY: /* IIR setting with
							     FIR = 1024 */
		mlx90614_power_get(data, false);
		mutex_lock(&data->lock);
		ret = i2c_smbus_read_word_data(data->client, MLX90614_CONFIG);
		mutex_unlock(&data->lock);
		mlx90614_power_put(data);

		if (ret < 0)
			return ret;

		*val = mlx90614_iir_values[ret & MLX90614_CONFIG_IIR_MASK] / 100;
		*val2 = (mlx90614_iir_values[ret & MLX90614_CONFIG_IIR_MASK] % 100) *
			10000;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}