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
struct zpa2326_private {scalar_t__ irq; int /*<<< orphan*/  timestamp; } ;
struct iio_poll_func {struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct zpa2326_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int iio_trigger_using_own (struct iio_dev*) ; 
 int /*<<< orphan*/  zpa2326_fill_sample_buffer (struct iio_dev*,struct zpa2326_private*) ; 
 scalar_t__ zpa2326_poll_oneshot_completion (struct iio_dev*) ; 
 int /*<<< orphan*/  zpa2326_sleep (struct iio_dev*) ; 
 scalar_t__ zpa2326_start_oneshot (struct iio_dev*) ; 
 scalar_t__ zpa2326_wait_oneshot_completion (struct iio_dev*,struct zpa2326_private*) ; 

__attribute__((used)) static irqreturn_t zpa2326_trigger_handler(int irq, void *data)
{
	struct iio_dev         *indio_dev = ((struct iio_poll_func *)
					     data)->indio_dev;
	struct zpa2326_private *priv = iio_priv(indio_dev);
	bool                    cont;

	/*
	 * We have been dispatched, meaning we are in triggered buffer mode.
	 * Using our own internal trigger implies we are currently in continuous
	 * hardware sampling mode.
	 */
	cont = iio_trigger_using_own(indio_dev);

	if (!cont) {
		/* On demand sampling : start a one shot cycle. */
		if (zpa2326_start_oneshot(indio_dev))
			goto out;

		/* Wait for sampling cycle to complete. */
		if (priv->irq <= 0) {
			/* No interrupt available: poll for completion. */
			if (zpa2326_poll_oneshot_completion(indio_dev))
				goto out;

			/* Only timestamp sample once it is ready. */
			priv->timestamp = iio_get_time_ns(indio_dev);
		} else {
			/* Interrupt handlers will timestamp for us. */
			if (zpa2326_wait_oneshot_completion(indio_dev, priv))
				goto out;
		}
	}

	/* Enqueue to IIO buffer / userspace. */
	zpa2326_fill_sample_buffer(indio_dev, priv);

out:
	if (!cont)
		/* Don't switch to low power if sampling continuously. */
		zpa2326_sleep(indio_dev);

	/* Inform attached trigger we are done. */
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}