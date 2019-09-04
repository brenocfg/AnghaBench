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
struct max30100_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  indio_dev; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct max30100_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max30100_fifo_count (struct max30100_data*) ; 
 int max30100_read_measurement (struct max30100_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t max30100_interrupt_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct max30100_data *data = iio_priv(indio_dev);
	int ret, cnt = 0;

	mutex_lock(&data->lock);

	while (cnt || (cnt = max30100_fifo_count(data)) > 0) {
		ret = max30100_read_measurement(data);
		if (ret)
			break;

		iio_push_to_buffers(data->indio_dev, data->buffer);
		cnt--;
	}

	mutex_unlock(&data->lock);

	return IRQ_HANDLED;
}