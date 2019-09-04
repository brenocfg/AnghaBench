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
struct sca3000_state {int* rx; int /*<<< orphan*/  lock; TYPE_1__* info; int /*<<< orphan*/  mo_det_use_count; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t address; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int scale; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IIO_ACCEL ; 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  SCA3000_REG_TEMP_MSB_ADDR ; 
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sca3000_addresses ; 
 int sca3000_read_3db_freq (struct sca3000_state*,int*) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_read_raw_samp_freq (struct sca3000_state*,int*) ; 

__attribute__((used)) static int sca3000_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val,
			    int *val2,
			    long mask)
{
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret;
	u8 address;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		if (chan->type == IIO_ACCEL) {
			if (st->mo_det_use_count) {
				mutex_unlock(&st->lock);
				return -EBUSY;
			}
			address = sca3000_addresses[chan->address][0];
			ret = sca3000_read_data_short(st, address, 2);
			if (ret < 0) {
				mutex_unlock(&st->lock);
				return ret;
			}
			*val = (be16_to_cpup((__be16 *)st->rx) >> 3) & 0x1FFF;
			*val = ((*val) << (sizeof(*val) * 8 - 13)) >>
				(sizeof(*val) * 8 - 13);
		} else {
			/* get the temperature when available */
			ret = sca3000_read_data_short(st,
						      SCA3000_REG_TEMP_MSB_ADDR,
						      2);
			if (ret < 0) {
				mutex_unlock(&st->lock);
				return ret;
			}
			*val = ((st->rx[0] & 0x3F) << 3) |
			       ((st->rx[1] & 0xE0) >> 5);
		}
		mutex_unlock(&st->lock);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		if (chan->type == IIO_ACCEL)
			*val2 = st->info->scale;
		else /* temperature */
			*val2 = 555556;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_OFFSET:
		*val = -214;
		*val2 = 600000;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&st->lock);
		ret = sca3000_read_raw_samp_freq(st, val);
		mutex_unlock(&st->lock);
		return ret ? ret : IIO_VAL_INT;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		mutex_lock(&st->lock);
		ret = sca3000_read_3db_freq(st, val);
		mutex_unlock(&st->lock);
		return ret;
	default:
		return -EINVAL;
	}
}