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
struct iio_dummy_state {int /*<<< orphan*/  event_timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t iio_simple_dummy_get_timestamp(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct iio_dummy_state *st = iio_priv(indio_dev);

	st->event_timestamp = iio_get_time_ns(indio_dev);
	return IRQ_WAKE_THREAD;
}