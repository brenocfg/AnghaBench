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
struct iio_dummy_state {int event_irq; int /*<<< orphan*/  regs; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int iio_dummy_evgen_get_irq () ; 
 int /*<<< orphan*/  iio_dummy_evgen_get_regs (int) ; 
 int /*<<< orphan*/  iio_dummy_evgen_release_irq (int) ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_simple_dummy_event_handler ; 
 int /*<<< orphan*/  iio_simple_dummy_get_timestamp ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct iio_dev*) ; 

int iio_simple_dummy_events_register(struct iio_dev *indio_dev)
{
	struct iio_dummy_state *st = iio_priv(indio_dev);
	int ret;

	/* Fire up event source - normally not present */
	st->event_irq = iio_dummy_evgen_get_irq();
	if (st->event_irq < 0) {
		ret = st->event_irq;
		goto error_ret;
	}
	st->regs = iio_dummy_evgen_get_regs(st->event_irq);

	ret = request_threaded_irq(st->event_irq,
				   &iio_simple_dummy_get_timestamp,
				   &iio_simple_dummy_event_handler,
				   IRQF_ONESHOT,
				   "iio_simple_event",
				   indio_dev);
	if (ret < 0)
		goto error_free_evgen;
	return 0;

error_free_evgen:
	iio_dummy_evgen_release_irq(st->event_irq);
error_ret:
	return ret;
}