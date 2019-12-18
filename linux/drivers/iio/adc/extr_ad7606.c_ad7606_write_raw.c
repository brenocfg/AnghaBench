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
struct iio_chan_spec {int address; } ;
struct ad7606_state {int (* write_scale ) (struct iio_dev*,int,int) ;int* range; int (* write_os ) (struct iio_dev*,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/ * oversampling_avail; int /*<<< orphan*/  oversampling; int /*<<< orphan*/  num_os_ratios; int /*<<< orphan*/  sw_mode_en; int /*<<< orphan*/  num_scales; int /*<<< orphan*/ * scale_avail; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int find_closest (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct iio_dev*,int,int) ; 
 int stub2 (struct iio_dev*,int) ; 

__attribute__((used)) static int ad7606_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val,
			    int val2,
			    long mask)
{
	struct ad7606_state *st = iio_priv(indio_dev);
	int i, ret, ch = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		mutex_lock(&st->lock);
		i = find_closest(val2, st->scale_avail, st->num_scales);
		if (st->sw_mode_en)
			ch = chan->address;
		ret = st->write_scale(indio_dev, ch, i);
		if (ret < 0) {
			mutex_unlock(&st->lock);
			return ret;
		}
		st->range[ch] = i;
		mutex_unlock(&st->lock);

		return 0;
	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		if (val2)
			return -EINVAL;
		i = find_closest(val, st->oversampling_avail,
				 st->num_os_ratios);
		mutex_lock(&st->lock);
		ret = st->write_os(indio_dev, i);
		if (ret < 0) {
			mutex_unlock(&st->lock);
			return ret;
		}
		st->oversampling = st->oversampling_avail[i];
		mutex_unlock(&st->lock);

		return 0;
	default:
		return -EINVAL;
	}
}