#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nau7802_state {size_t sample_rate; int vref_mv; TYPE_1__* client; int /*<<< orphan*/  lock; int /*<<< orphan*/  conversion_count; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int NAU7802_CTRL1_GAINS_BITS ; 
 int NAU7802_CTRL2_CHS (int /*<<< orphan*/ ) ; 
 int NAU7802_CTRL2_CHS_BIT ; 
 int NAU7802_CTRL2_CRS (size_t) ; 
 int /*<<< orphan*/  NAU7802_REG_CTRL1 ; 
 int /*<<< orphan*/  NAU7802_REG_CTRL2 ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct nau7802_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nau7802_read_irq (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int nau7802_read_poll (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int* nau7802_sample_freq_avail ; 

__attribute__((used)) static int nau7802_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct nau7802_state *st = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		/*
		 * Select the channel to use
		 *   - Channel 1 is value 0 in the CHS register
		 *   - Channel 2 is value 1 in the CHS register
		 */
		ret = i2c_smbus_read_byte_data(st->client, NAU7802_REG_CTRL2);
		if (ret < 0) {
			mutex_unlock(&st->lock);
			return ret;
		}

		if (((ret & NAU7802_CTRL2_CHS_BIT) && !chan->channel) ||
				(!(ret & NAU7802_CTRL2_CHS_BIT) &&
				 chan->channel)) {
			st->conversion_count = 0;
			ret = i2c_smbus_write_byte_data(st->client,
					NAU7802_REG_CTRL2,
					NAU7802_CTRL2_CHS(chan->channel) |
					NAU7802_CTRL2_CRS(st->sample_rate));

			if (ret < 0) {
				mutex_unlock(&st->lock);
				return ret;
			}
		}

		if (st->client->irq)
			ret = nau7802_read_irq(indio_dev, chan, val);
		else
			ret = nau7802_read_poll(indio_dev, chan, val);

		mutex_unlock(&st->lock);
		return ret;

	case IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_read_byte_data(st->client, NAU7802_REG_CTRL1);
		if (ret < 0)
			return ret;

		/*
		 * We have 24 bits of signed data, that means 23 bits of data
		 * plus the sign bit
		 */
		*val = st->vref_mv;
		*val2 = 23 + (ret & NAU7802_CTRL1_GAINS_BITS);

		return IIO_VAL_FRACTIONAL_LOG2;

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val =  nau7802_sample_freq_avail[st->sample_rate];
		*val2 = 0;
		return IIO_VAL_INT;

	default:
		break;
	}

	return -EINVAL;
}