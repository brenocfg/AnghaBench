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
struct zpa2326_private {int /*<<< orphan*/  irq; scalar_t__ waken; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct zpa2326_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_using_own (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int zpa2326_clear_fifo (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int zpa2326_config_oneshot (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpa2326_err (struct iio_dev*,char*,int) ; 

__attribute__((used)) static int zpa2326_postenable_buffer(struct iio_dev *indio_dev)
{
	const struct zpa2326_private *priv = iio_priv(indio_dev);
	int                           err;

	if (!priv->waken) {
		/*
		 * We were already power supplied. Just clear hardware FIFO to
		 * get rid of samples acquired during previous rounds (if any).
		 */
		err = zpa2326_clear_fifo(indio_dev, 0);
		if (err)
			goto err;
	}

	if (!iio_trigger_using_own(indio_dev) && priv->waken) {
		/*
		 * We are using an external trigger and we have just been
		 * powered up: reconfigure one-shot mode.
		 */
		err = zpa2326_config_oneshot(indio_dev, priv->irq);
		if (err)
			goto err;
	}

	/* Plug our own trigger event handler. */
	err = iio_triggered_buffer_postenable(indio_dev);
	if (err)
		goto err;

	return 0;

err:
	zpa2326_err(indio_dev, "failed to enable buffering (%d)", err);

	return err;
}