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
struct hts221_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HTS221_SENSOR_H ; 
 int /*<<< orphan*/  HTS221_SENSOR_T ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 131 
#define  IIO_CHAN_INFO_SAMP_FREQ 130 
#define  IIO_HUMIDITYRELATIVE 129 
#define  IIO_TEMP 128 
 int hts221_update_avg (struct hts221_hw*,int /*<<< orphan*/ ,int) ; 
 int hts221_update_odr (struct hts221_hw*,int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct hts221_hw* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int hts221_write_raw(struct iio_dev *iio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct hts221_hw *hw = iio_priv(iio_dev);
	int ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	if (ret)
		return ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = hts221_update_odr(hw, val);
		break;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->type) {
		case IIO_HUMIDITYRELATIVE:
			ret = hts221_update_avg(hw, HTS221_SENSOR_H, val);
			break;
		case IIO_TEMP:
			ret = hts221_update_avg(hw, HTS221_SENSOR_T, val);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	iio_device_release_direct_mode(iio_dev);

	return ret;
}