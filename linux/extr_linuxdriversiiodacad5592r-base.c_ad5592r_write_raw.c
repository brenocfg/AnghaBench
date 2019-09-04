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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct TYPE_3__ {int realbits; } ;
struct iio_chan_spec {size_t channel; int /*<<< orphan*/  output; int /*<<< orphan*/  type; TYPE_1__ scan_type; } ;
struct ad5592r_state {int* cached_dac; int** scale_avail; int /*<<< orphan*/  cached_gp_ctrl; TYPE_2__* ops; } ;
struct TYPE_4__ {int (* write_dac ) (struct ad5592r_state*,size_t,int) ;int (* reg_read ) (struct ad5592r_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* reg_write ) (struct ad5592r_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AD5592R_REG_CTRL ; 
 int /*<<< orphan*/  AD5592R_REG_CTRL_ADC_RANGE ; 
 int /*<<< orphan*/  AD5592R_REG_CTRL_DAC_RANGE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 struct ad5592r_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ad5592r_state*,size_t,int) ; 
 int stub2 (struct ad5592r_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub3 (struct ad5592r_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5592r_write_raw(struct iio_dev *iio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	struct ad5592r_state *st = iio_priv(iio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:

		if (val >= (1 << chan->scan_type.realbits) || val < 0)
			return -EINVAL;

		if (!chan->output)
			return -EINVAL;

		mutex_lock(&iio_dev->mlock);
		ret = st->ops->write_dac(st, chan->channel, val);
		if (!ret)
			st->cached_dac[chan->channel] = val;
		mutex_unlock(&iio_dev->mlock);
		return ret;
	case IIO_CHAN_INFO_SCALE:
		if (chan->type == IIO_VOLTAGE) {
			bool gain;

			if (val == st->scale_avail[0][0] &&
				val2 == st->scale_avail[0][1])
				gain = false;
			else if (val == st->scale_avail[1][0] &&
				 val2 == st->scale_avail[1][1])
				gain = true;
			else
				return -EINVAL;

			mutex_lock(&iio_dev->mlock);

			ret = st->ops->reg_read(st, AD5592R_REG_CTRL,
						&st->cached_gp_ctrl);
			if (ret < 0) {
				mutex_unlock(&iio_dev->mlock);
				return ret;
			}

			if (chan->output) {
				if (gain)
					st->cached_gp_ctrl |=
						AD5592R_REG_CTRL_DAC_RANGE;
				else
					st->cached_gp_ctrl &=
						~AD5592R_REG_CTRL_DAC_RANGE;
			} else {
				if (gain)
					st->cached_gp_ctrl |=
						AD5592R_REG_CTRL_ADC_RANGE;
				else
					st->cached_gp_ctrl &=
						~AD5592R_REG_CTRL_ADC_RANGE;
			}

			ret = st->ops->reg_write(st, AD5592R_REG_CTRL,
						 st->cached_gp_ctrl);
			mutex_unlock(&iio_dev->mlock);

			return ret;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}