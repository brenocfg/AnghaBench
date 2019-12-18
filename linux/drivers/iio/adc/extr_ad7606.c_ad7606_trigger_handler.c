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
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct ad7606_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio_convst; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ad7606_read_samples (struct ad7606_state*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ad7606_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct ad7606_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->lock);

	ret = ad7606_read_samples(st);
	if (ret == 0)
		iio_push_to_buffers_with_timestamp(indio_dev, st->data,
						   iio_get_time_ns(indio_dev));

	iio_trigger_notify_done(indio_dev->trig);
	/* The rising edge of the CONVST signal starts a new conversion. */
	gpiod_set_value(st->gpio_convst, 1);

	mutex_unlock(&st->lock);

	return IRQ_HANDLED;
}