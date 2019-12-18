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
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/ * active_scan_mask; int /*<<< orphan*/  scan_bytes; } ;
struct cros_ec_sensors_core_state {int (* read_ec_sensors_data ) (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cmd_lock; scalar_t__ samples; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t cros_ec_sensors_capture(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->cmd_lock);

	/* Clear capture data. */
	memset(st->samples, 0, indio_dev->scan_bytes);

	/* Read data based on which channels are enabled in scan mask. */
	ret = st->read_ec_sensors_data(indio_dev,
				       *(indio_dev->active_scan_mask),
				       (s16 *)st->samples);
	if (ret < 0)
		goto done;

	iio_push_to_buffers_with_timestamp(indio_dev, st->samples,
					   iio_get_time_ns(indio_dev));

done:
	/*
	 * Tell the core we are done with this trigger and ready for the
	 * next one.
	 */
	iio_trigger_notify_done(indio_dev->trig);

	mutex_unlock(&st->cmd_lock);

	return IRQ_HANDLED;
}