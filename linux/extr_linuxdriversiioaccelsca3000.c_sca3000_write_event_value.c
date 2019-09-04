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
typedef  int u8 ;
struct sca3000_state {int /*<<< orphan*/  lock; TYPE_1__* info; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ channel2; size_t address; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
struct TYPE_2__ {int* mot_det_mult_y; int* mot_det_mult_xz; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ IIO_MOD_Y ; 
 struct sca3000_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sca3000_addresses ; 
 int sca3000_write_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_write_event_value(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     enum iio_event_info info,
				     int val, int val2)
{
	struct sca3000_state *st = iio_priv(indio_dev);
	int ret;
	int i;
	u8 nonlinear = 0;

	if (chan->channel2 == IIO_MOD_Y) {
		i = ARRAY_SIZE(st->info->mot_det_mult_y);
		while (i > 0)
			if (val >= st->info->mot_det_mult_y[--i]) {
				nonlinear |= (1 << i);
				val -= st->info->mot_det_mult_y[i];
			}
	} else {
		i = ARRAY_SIZE(st->info->mot_det_mult_xz);
		while (i > 0)
			if (val >= st->info->mot_det_mult_xz[--i]) {
				nonlinear |= (1 << i);
				val -= st->info->mot_det_mult_xz[i];
			}
	}

	mutex_lock(&st->lock);
	ret = sca3000_write_ctrl_reg(st,
				     sca3000_addresses[chan->address][1],
				     nonlinear);
	mutex_unlock(&st->lock);

	return ret;
}