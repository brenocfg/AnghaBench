#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct sgp_crc_word* raw_words; } ;
struct TYPE_3__ {struct sgp_crc_word* raw_words; } ;
struct sgp_data {int /*<<< orphan*/  data_lock; TYPE_2__ buffer; int /*<<< orphan*/  measure_gas_signals_cmd; TYPE_1__ iaq_buffer; int /*<<< orphan*/  iaq_buffer_state; } ;
struct sgp_crc_word {int /*<<< orphan*/  value; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int address; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IAQ_BUFFER_EMPTY ; 
 int /*<<< orphan*/  IAQ_BUFFER_VALID ; 
#define  IIO_CHAN_INFO_PROCESSED 135 
#define  IIO_CHAN_INFO_RAW 134 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  SGP30_IAQ_CO2EQ_IDX 133 
#define  SGP30_IAQ_TVOC_IDX 132 
#define  SGP30_SIG_ETOH_IDX 131 
#define  SGP30_SIG_H2_IDX 130 
#define  SGPC3_IAQ_TVOC_IDX 129 
#define  SGPC3_SIG_ETOH_IDX 128 
 int /*<<< orphan*/  SGP_MEASUREMENT_DURATION_US ; 
 int /*<<< orphan*/  SGP_MEASUREMENT_LEN ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct sgp_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sgp_read_cmd (struct sgp_data*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sgp_read_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan, int *val,
			int *val2, long mask)
{
	struct sgp_data *data = iio_priv(indio_dev);
	struct sgp_crc_word *words;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&data->data_lock);
		if (data->iaq_buffer_state != IAQ_BUFFER_VALID) {
			mutex_unlock(&data->data_lock);
			return -EBUSY;
		}
		words = data->iaq_buffer.raw_words;
		switch (chan->address) {
		case SGP30_IAQ_TVOC_IDX:
		case SGPC3_IAQ_TVOC_IDX:
			*val = 0;
			*val2 = be16_to_cpu(words[1].value);
			ret = IIO_VAL_INT_PLUS_NANO;
			break;
		case SGP30_IAQ_CO2EQ_IDX:
			*val = 0;
			*val2 = be16_to_cpu(words[0].value);
			ret = IIO_VAL_INT_PLUS_MICRO;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		mutex_unlock(&data->data_lock);
		break;
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&data->data_lock);
		if (chan->address == SGPC3_SIG_ETOH_IDX) {
			if (data->iaq_buffer_state == IAQ_BUFFER_EMPTY)
				ret = -EBUSY;
			else
				ret = 0;
			words = data->iaq_buffer.raw_words;
		} else {
			ret = sgp_read_cmd(data, data->measure_gas_signals_cmd,
					   &data->buffer, SGP_MEASUREMENT_LEN,
					   SGP_MEASUREMENT_DURATION_US);
			words = data->buffer.raw_words;
		}
		if (ret) {
			mutex_unlock(&data->data_lock);
			return ret;
		}

		switch (chan->address) {
		case SGP30_SIG_ETOH_IDX:
			*val = be16_to_cpu(words[1].value);
			ret = IIO_VAL_INT;
			break;
		case SGPC3_SIG_ETOH_IDX:
		case SGP30_SIG_H2_IDX:
			*val = be16_to_cpu(words[0].value);
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		mutex_unlock(&data->data_lock);
		break;
	default:
		return -EINVAL;
	}

	return ret;
}