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
struct rpr0521_data {int /*<<< orphan*/  irq_timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct rpr0521_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t rpr0521_drdy_irq_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct rpr0521_data *data = iio_priv(indio_dev);

	data->irq_timestamp = iio_get_time_ns(indio_dev);
	/*
	 * We need to wake the thread to read the interrupt reg. It
	 * is not possible to do that here because regmap_read takes a
	 * mutex.
	 */

	return IRQ_WAKE_THREAD;
}