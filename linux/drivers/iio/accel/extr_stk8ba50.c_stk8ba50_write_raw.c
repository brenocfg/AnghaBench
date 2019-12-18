#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stk8ba50_data {int range; int sample_rate_idx; TYPE_3__* client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int scale_val; int samp_freq; int /*<<< orphan*/  reg_val; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  STK8BA50_REG_BWSEL ; 
 int /*<<< orphan*/  STK8BA50_REG_RANGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stk8ba50_data* iio_priv (struct iio_dev*) ; 
 TYPE_1__* stk8ba50_samp_freq_table ; 
 TYPE_1__* stk8ba50_scale_table ; 

__attribute__((used)) static int stk8ba50_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int val, int val2, long mask)
{
	int ret;
	int i;
	int index = -1;
	struct stk8ba50_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		if (val != 0)
			return -EINVAL;

		for (i = 0; i < ARRAY_SIZE(stk8ba50_scale_table); i++)
			if (val2 == stk8ba50_scale_table[i].scale_val) {
				index = i;
				break;
			}
		if (index < 0)
			return -EINVAL;

		ret = i2c_smbus_write_byte_data(data->client,
				STK8BA50_REG_RANGE,
				stk8ba50_scale_table[index].reg_val);
		if (ret < 0)
			dev_err(&data->client->dev,
					"failed to set measurement range\n");
		else
			data->range = index;

		return ret;
	case IIO_CHAN_INFO_SAMP_FREQ:
		for (i = 0; i < ARRAY_SIZE(stk8ba50_samp_freq_table); i++)
			if (val == stk8ba50_samp_freq_table[i].samp_freq) {
				index = i;
				break;
			}
		if (index < 0)
			return -EINVAL;

		ret = i2c_smbus_write_byte_data(data->client,
				STK8BA50_REG_BWSEL,
				stk8ba50_samp_freq_table[index].reg_val);
		if (ret < 0)
			dev_err(&data->client->dev,
					"failed to set sampling rate\n");
		else
			data->sample_rate_idx = index;

		return ret;
	}

	return -EINVAL;
}