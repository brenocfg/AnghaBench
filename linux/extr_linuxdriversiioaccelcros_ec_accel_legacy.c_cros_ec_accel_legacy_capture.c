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
struct iio_dev {int /*<<< orphan*/  trig; int /*<<< orphan*/ * active_scan_mask; } ;
struct cros_ec_accel_legacy_state {scalar_t__ capture_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct cros_ec_accel_legacy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_ec_accel_data (struct cros_ec_accel_legacy_state*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t cros_ec_accel_legacy_capture(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct cros_ec_accel_legacy_state *st = iio_priv(indio_dev);

	/* Clear capture data. */
	memset(st->capture_data, 0, sizeof(st->capture_data));

	/*
	 * Read data based on which channels are enabled in scan mask. Note
	 * that on a capture we are always reading the calibrated data.
	 */
	read_ec_accel_data(st, *indio_dev->active_scan_mask, st->capture_data);

	iio_push_to_buffers_with_timestamp(indio_dev, (void *)st->capture_data,
					   iio_get_time_ns(indio_dev));

	/*
	 * Tell the core we are done with this trigger and ready for the
	 * next one.
	 */
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}