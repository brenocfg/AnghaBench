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
struct max30102_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  processed_buffer; int /*<<< orphan*/  indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  masklength; int /*<<< orphan*/  active_scan_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max30102_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max30102_fifo_count (struct max30102_data*) ; 
 int max30102_read_measurement (struct max30102_data*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t max30102_interrupt_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct max30102_data *data = iio_priv(indio_dev);
	unsigned int measurements = bitmap_weight(indio_dev->active_scan_mask,
						  indio_dev->masklength);
	int ret, cnt = 0;

	mutex_lock(&data->lock);

	while (cnt || (cnt = max30102_fifo_count(data)) > 0) {
		ret = max30102_read_measurement(data, measurements);
		if (ret)
			break;

		iio_push_to_buffers(data->indio_dev, data->processed_buffer);
		cnt--;
	}

	mutex_unlock(&data->lock);

	return IRQ_HANDLED;
}