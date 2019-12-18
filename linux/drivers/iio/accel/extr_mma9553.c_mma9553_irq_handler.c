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
struct mma9553_data {int /*<<< orphan*/  timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t mma9553_irq_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct mma9553_data *data = iio_priv(indio_dev);

	data->timestamp = iio_get_time_ns(indio_dev);
	/*
	 * Since we only configure the interrupt pin when an
	 * event is enabled, we are sure we have at least
	 * one event enabled at this point.
	 */
	return IRQ_WAKE_THREAD;
}