#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int address; } ;
struct TYPE_2__ {int /*<<< orphan*/  voc_ppb; int /*<<< orphan*/  resistance; int /*<<< orphan*/  co2_ppm; } ;
struct ams_iaqcore_data {int /*<<< orphan*/  lock; TYPE_1__ buffer; } ;

/* Variables and functions */
#define  AMS_IAQCORE_VOC_CO2_IDX 130 
#define  AMS_IAQCORE_VOC_RESISTANCE_IDX 129 
#define  AMS_IAQCORE_VOC_TVOC_IDX 128 
 int EINVAL ; 
 long IIO_CHAN_INFO_PROCESSED ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int ams_iaqcore_get_measurement (struct ams_iaqcore_data*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ams_iaqcore_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ams_iaqcore_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan, int *val,
				int *val2, long mask)
{
	struct ams_iaqcore_data *data = iio_priv(indio_dev);
	int ret;

	if (mask != IIO_CHAN_INFO_PROCESSED)
		return -EINVAL;

	mutex_lock(&data->lock);
	ret = ams_iaqcore_get_measurement(data);

	if (ret)
		goto err_out;

	switch (chan->address) {
	case AMS_IAQCORE_VOC_CO2_IDX:
		*val = 0;
		*val2 = be16_to_cpu(data->buffer.co2_ppm);
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	case AMS_IAQCORE_VOC_RESISTANCE_IDX:
		*val = be32_to_cpu(data->buffer.resistance);
		ret = IIO_VAL_INT;
		break;
	case AMS_IAQCORE_VOC_TVOC_IDX:
		*val = 0;
		*val2 = be16_to_cpu(data->buffer.voc_ppb);
		ret = IIO_VAL_INT_PLUS_NANO;
		break;
	default:
		ret = -EINVAL;
	}

err_out:
	mutex_unlock(&data->lock);

	return ret;
}