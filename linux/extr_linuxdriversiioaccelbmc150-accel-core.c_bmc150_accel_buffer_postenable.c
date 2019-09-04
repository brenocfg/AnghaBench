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
struct iio_dev {scalar_t__ currentmode; } ;
struct bmc150_accel_data {int /*<<< orphan*/  mutex; scalar_t__ fifo_mode; int /*<<< orphan*/  watermark; } ;

/* Variables and functions */
 scalar_t__ BMC150_ACCEL_FIFO_MODE_FIFO ; 
 int /*<<< orphan*/  BMC150_ACCEL_INT_WATERMARK ; 
 scalar_t__ INDIO_BUFFER_TRIGGERED ; 
 int bmc150_accel_fifo_set_mode (struct bmc150_accel_data*) ; 
 int bmc150_accel_set_interrupt (struct bmc150_accel_data*,int /*<<< orphan*/ ,int) ; 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmc150_accel_buffer_postenable(struct iio_dev *indio_dev)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);
	int ret = 0;

	if (indio_dev->currentmode == INDIO_BUFFER_TRIGGERED)
		return iio_triggered_buffer_postenable(indio_dev);

	mutex_lock(&data->mutex);

	if (!data->watermark)
		goto out;

	ret = bmc150_accel_set_interrupt(data, BMC150_ACCEL_INT_WATERMARK,
					 true);
	if (ret)
		goto out;

	data->fifo_mode = BMC150_ACCEL_FIFO_MODE_FIFO;

	ret = bmc150_accel_fifo_set_mode(data);
	if (ret) {
		data->fifo_mode = 0;
		bmc150_accel_set_interrupt(data, BMC150_ACCEL_INT_WATERMARK,
					   false);
	}

out:
	mutex_unlock(&data->mutex);

	return ret;
}