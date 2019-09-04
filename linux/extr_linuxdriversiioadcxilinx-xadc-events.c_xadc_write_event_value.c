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
struct xadc {int* threshold; int temp_hysteresis; int /*<<< orphan*/  mutex; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_INFO_HYSTERESIS 129 
#define  IIO_EV_INFO_VALUE 128 
 scalar_t__ IIO_TEMP ; 
 int /*<<< orphan*/  XADC_REG_THRESHOLD (unsigned int) ; 
 int XADC_THRESHOLD_VALUE_SHIFT ; 
 int _xadc_write_adc_reg (struct xadc*,int /*<<< orphan*/ ,int) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int xadc_get_threshold_offset (struct iio_chan_spec const*,int) ; 

int xadc_write_event_value(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info,
	int val, int val2)
{
	unsigned int offset = xadc_get_threshold_offset(chan, dir);
	struct xadc *xadc = iio_priv(indio_dev);
	int ret = 0;

	val <<= XADC_THRESHOLD_VALUE_SHIFT;

	if (val < 0 || val > 0xffff)
		return -EINVAL;

	mutex_lock(&xadc->mutex);

	switch (info) {
	case IIO_EV_INFO_VALUE:
		xadc->threshold[offset] = val;
		break;
	case IIO_EV_INFO_HYSTERESIS:
		xadc->temp_hysteresis = val;
		break;
	default:
		mutex_unlock(&xadc->mutex);
		return -EINVAL;
	}

	if (chan->type == IIO_TEMP) {
		/*
		 * According to the datasheet we need to set the lower 4 bits to
		 * 0x3, otherwise 125 degree celsius will be used as the
		 * threshold.
		 */
		val |= 0x3;

		/*
		 * Since we store the hysteresis as relative (to the threshold)
		 * value, but the hardware expects an absolute value we need to
		 * recalcualte this value whenever the hysteresis or the
		 * threshold changes.
		 */
		if (xadc->threshold[offset] < xadc->temp_hysteresis)
			xadc->threshold[offset + 4] = 0;
		else
			xadc->threshold[offset + 4] = xadc->threshold[offset] -
					xadc->temp_hysteresis;
		ret = _xadc_write_adc_reg(xadc, XADC_REG_THRESHOLD(offset + 4),
			xadc->threshold[offset + 4]);
		if (ret)
			goto out_unlock;
	}

	if (info == IIO_EV_INFO_VALUE)
		ret = _xadc_write_adc_reg(xadc, XADC_REG_THRESHOLD(offset), val);

out_unlock:
	mutex_unlock(&xadc->mutex);

	return ret;
}