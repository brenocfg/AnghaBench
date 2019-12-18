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
struct nau7802_state {int* scale_avail; int sample_rate; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; int /*<<< orphan*/  conversion_count; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  NAU7802_CTRL2_CRS (int) ; 
 int /*<<< orphan*/  NAU7802_REG_CTRL2 ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nau7802_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* nau7802_sample_freq_avail ; 
 int nau7802_set_gain (struct nau7802_state*,int) ; 

__attribute__((used)) static int nau7802_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val, int val2, long mask)
{
	struct nau7802_state *st = iio_priv(indio_dev);
	int i, ret;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		for (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
			if (val2 == st->scale_avail[i])
				return nau7802_set_gain(st, i);

		break;

	case IIO_CHAN_INFO_SAMP_FREQ:
		for (i = 0; i < ARRAY_SIZE(nau7802_sample_freq_avail); i++)
			if (val == nau7802_sample_freq_avail[i]) {
				mutex_lock(&st->lock);
				st->sample_rate = i;
				st->conversion_count = 0;
				ret = i2c_smbus_write_byte_data(st->client,
					NAU7802_REG_CTRL2,
					NAU7802_CTRL2_CRS(st->sample_rate));
				mutex_unlock(&st->lock);
				return ret;
			}

		break;

	default:
		break;
	}

	return -EINVAL;
}