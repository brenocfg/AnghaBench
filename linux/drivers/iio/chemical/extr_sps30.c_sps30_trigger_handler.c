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
struct sps30_state {int /*<<< orphan*/  lock; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct sps30_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sps30_do_meas (struct sps30_state*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t sps30_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct sps30_state *state = iio_priv(indio_dev);
	int ret;
	s32 data[4 + 2]; /* PM1, PM2P5, PM4, PM10, timestamp */

	mutex_lock(&state->lock);
	ret = sps30_do_meas(state, data, 4);
	mutex_unlock(&state->lock);
	if (ret)
		goto err;

	iio_push_to_buffers_with_timestamp(indio_dev, data,
					   iio_get_time_ns(indio_dev));
err:
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}