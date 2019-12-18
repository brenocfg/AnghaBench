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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct hp206c_osr_setting {int osr_mask; int /*<<< orphan*/  pres_conv_time_us; int /*<<< orphan*/  temp_conv_time_us; } ;
struct hp206c_data {size_t temp_osr_index; size_t pres_osr_index; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int HP206C_CMD_ADC_CVT ; 
 int HP206C_CMD_ADC_CVT_CHNL_PT ; 
 int HP206C_CMD_ADC_CVT_CHNL_T ; 
 int /*<<< orphan*/  HP206C_CMD_READ_P ; 
 int /*<<< orphan*/  HP206C_CMD_READ_T ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int hp206c_conv_and_read (struct iio_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* hp206c_osr_rates ; 
 struct hp206c_osr_setting* hp206c_osr_settings ; 
 struct hp206c_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int hp206c_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan, int *val,
			   int *val2, long mask)
{
	int ret;
	struct hp206c_data *data = iio_priv(indio_dev);
	const struct hp206c_osr_setting *osr_setting;
	u8 conv_cmd;

	mutex_lock(&data->mutex);

	switch (mask) {
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->type) {
		case IIO_TEMP:
			*val = hp206c_osr_rates[data->temp_osr_index];
			ret = IIO_VAL_INT;
			break;

		case IIO_PRESSURE:
			*val = hp206c_osr_rates[data->pres_osr_index];
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
		}
		break;

	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_TEMP:
			osr_setting = &hp206c_osr_settings[data->temp_osr_index];
			conv_cmd = HP206C_CMD_ADC_CVT |
					osr_setting->osr_mask |
					HP206C_CMD_ADC_CVT_CHNL_T;
			ret = hp206c_conv_and_read(indio_dev,
					conv_cmd,
					HP206C_CMD_READ_T,
					osr_setting->temp_conv_time_us);
			if (ret >= 0) {
				/* 20 significant bits are provided.
				 * Extend sign over the rest.
				 */
				*val = sign_extend32(ret, 19);
				ret = IIO_VAL_INT;
			}
			break;

		case IIO_PRESSURE:
			osr_setting = &hp206c_osr_settings[data->pres_osr_index];
			conv_cmd = HP206C_CMD_ADC_CVT |
					osr_setting->osr_mask |
					HP206C_CMD_ADC_CVT_CHNL_PT;
			ret = hp206c_conv_and_read(indio_dev,
					conv_cmd,
					HP206C_CMD_READ_P,
					osr_setting->pres_conv_time_us);
			if (ret >= 0) {
				*val = ret;
				ret = IIO_VAL_INT;
			}
			break;
		default:
			ret = -EINVAL;
		}
		break;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_TEMP:
			*val = 0;
			*val2 = 10000;
			ret = IIO_VAL_INT_PLUS_MICRO;
			break;

		case IIO_PRESSURE:
			*val = 0;
			*val2 = 1000;
			ret = IIO_VAL_INT_PLUS_MICRO;
			break;
		default:
			ret = -EINVAL;
		}
		break;

	default:
		ret = -EINVAL;
	}

	mutex_unlock(&data->mutex);
	return ret;
}