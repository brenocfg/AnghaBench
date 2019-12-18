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
struct stk3310_data {int /*<<< orphan*/  timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct stk3310_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t stk3310_irq_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct stk3310_data *data = iio_priv(indio_dev);

	data->timestamp = iio_get_time_ns(indio_dev);

	return IRQ_WAKE_THREAD;
}