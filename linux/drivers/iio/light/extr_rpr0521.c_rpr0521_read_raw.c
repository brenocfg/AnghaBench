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
typedef  int /*<<< orphan*/  u8 ;
struct rpr0521_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  raw_data ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  address; int /*<<< orphan*/  device_mask; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_INTENSITY ; 
 int /*<<< orphan*/  IIO_PROXIMITY ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* rpr0521_data_reg ; 
 int rpr0521_get_gain (struct rpr0521_data*,size_t,int*,int*) ; 
 int rpr0521_read_ps_offset (struct rpr0521_data*,int*) ; 
 int rpr0521_read_samp_freq (struct rpr0521_data*,int /*<<< orphan*/ ,int*,int*) ; 
 int rpr0521_set_power_state (struct rpr0521_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpr0521_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan, int *val,
			    int *val2, long mask)
{
	struct rpr0521_data *data = iio_priv(indio_dev);
	int ret;
	int busy;
	u8 device_mask;
	__le16 raw_data;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type != IIO_INTENSITY && chan->type != IIO_PROXIMITY)
			return -EINVAL;

		busy = iio_device_claim_direct_mode(indio_dev);
		if (busy)
			return -EBUSY;

		device_mask = rpr0521_data_reg[chan->address].device_mask;

		mutex_lock(&data->lock);
		ret = rpr0521_set_power_state(data, true, device_mask);
		if (ret < 0)
			goto rpr0521_read_raw_out;

		ret = regmap_bulk_read(data->regmap,
				       rpr0521_data_reg[chan->address].address,
				       &raw_data, sizeof(raw_data));
		if (ret < 0) {
			rpr0521_set_power_state(data, false, device_mask);
			goto rpr0521_read_raw_out;
		}

		ret = rpr0521_set_power_state(data, false, device_mask);

rpr0521_read_raw_out:
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);
		if (ret < 0)
			return ret;

		*val = le16_to_cpu(raw_data);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		mutex_lock(&data->lock);
		ret = rpr0521_get_gain(data, chan->address, val, val2);
		mutex_unlock(&data->lock);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->lock);
		ret = rpr0521_read_samp_freq(data, chan->type, val, val2);
		mutex_unlock(&data->lock);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT_PLUS_MICRO;

	case IIO_CHAN_INFO_OFFSET:
		mutex_lock(&data->lock);
		ret = rpr0521_read_ps_offset(data, val);
		mutex_unlock(&data->lock);
		if (ret < 0)
			return ret;

		return IIO_VAL_INT;

	default:
		return -EINVAL;
	}
}