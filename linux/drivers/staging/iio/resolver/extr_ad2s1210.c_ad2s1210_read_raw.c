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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; } ;
struct ad2s1210_state {int* rx; int resolution; int /*<<< orphan*/  lock; int /*<<< orphan*/ * gpios; int /*<<< orphan*/  hysteresis; int /*<<< orphan*/  sdev; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 size_t AD2S1210_SAMPLE ; 
 int EINVAL ; 
#define  IIO_ANGL 129 
#define  IIO_ANGL_VEL 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MOD_POS ; 
 int /*<<< orphan*/  MOD_VEL ; 
 int /*<<< orphan*/  ad2s1210_set_mode (int /*<<< orphan*/ ,struct ad2s1210_state*) ; 
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad2s1210_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ad2s1210_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val,
			     int *val2,
			     long m)
{
	struct ad2s1210_state *st = iio_priv(indio_dev);
	u16 negative;
	int ret = 0;
	u16 pos;
	s16 vel;

	mutex_lock(&st->lock);
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 0);
	/* delay (6 * tck + 20) nano seconds */
	udelay(1);

	switch (chan->type) {
	case IIO_ANGL:
		ad2s1210_set_mode(MOD_POS, st);
		break;
	case IIO_ANGL_VEL:
		ad2s1210_set_mode(MOD_VEL, st);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	if (ret < 0)
		goto error_ret;
	ret = spi_read(st->sdev, st->rx, 2);
	if (ret < 0)
		goto error_ret;

	switch (chan->type) {
	case IIO_ANGL:
		pos = be16_to_cpup((__be16 *)st->rx);
		if (st->hysteresis)
			pos >>= 16 - st->resolution;
		*val = pos;
		ret = IIO_VAL_INT;
		break;
	case IIO_ANGL_VEL:
		negative = st->rx[0] & 0x80;
		vel = be16_to_cpup((__be16 *)st->rx);
		vel >>= 16 - st->resolution;
		if (vel & 0x8000) {
			negative = (0xffff >> st->resolution) << st->resolution;
			vel |= negative;
		}
		*val = vel;
		ret = IIO_VAL_INT;
		break;
	default:
		mutex_unlock(&st->lock);
		return -EINVAL;
	}

error_ret:
	gpiod_set_value(st->gpios[AD2S1210_SAMPLE], 1);
	/* delay (2 * tck + 20) nano seconds */
	udelay(1);
	mutex_unlock(&st->lock);
	return ret;
}