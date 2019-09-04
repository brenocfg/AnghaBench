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
struct iio_dummy_state {int /*<<< orphan*/  event_irq; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_dummy_evgen_release_irq (int /*<<< orphan*/ ) ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 

void iio_simple_dummy_events_unregister(struct iio_dev *indio_dev)
{
	struct iio_dummy_state *st = iio_priv(indio_dev);

	free_irq(st->event_irq, indio_dev);
	/* Not part of normal driver */
	iio_dummy_evgen_release_irq(st->event_irq);
}