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
struct TYPE_3__ {unsigned int realbits; unsigned int shift; } ;
struct iio_chan_spec {TYPE_1__ scan_type; } ;
struct ad5446_state {int pwr_down; unsigned int pwr_down_mode; unsigned int cached_val; TYPE_2__* chip_info; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int (* write ) (struct ad5446_state*,unsigned int) ;} ;

/* Variables and functions */
 struct ad5446_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct ad5446_state*,unsigned int) ; 

__attribute__((used)) static ssize_t ad5446_write_dac_powerdown(struct iio_dev *indio_dev,
					    uintptr_t private,
					    const struct iio_chan_spec *chan,
					    const char *buf, size_t len)
{
	struct ad5446_state *st = iio_priv(indio_dev);
	unsigned int shift;
	unsigned int val;
	bool powerdown;
	int ret;

	ret = strtobool(buf, &powerdown);
	if (ret)
		return ret;

	mutex_lock(&indio_dev->mlock);
	st->pwr_down = powerdown;

	if (st->pwr_down) {
		shift = chan->scan_type.realbits + chan->scan_type.shift;
		val = st->pwr_down_mode << shift;
	} else {
		val = st->cached_val;
	}

	ret = st->chip_info->write(st, val);
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}