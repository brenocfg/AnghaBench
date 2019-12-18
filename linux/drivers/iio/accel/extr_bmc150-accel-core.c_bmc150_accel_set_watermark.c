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
struct iio_dev {int dummy; } ;
struct bmc150_accel_data {unsigned int watermark; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned int BMC150_ACCEL_FIFO_LENGTH ; 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmc150_accel_set_watermark(struct iio_dev *indio_dev, unsigned val)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);

	if (val > BMC150_ACCEL_FIFO_LENGTH)
		val = BMC150_ACCEL_FIFO_LENGTH;

	mutex_lock(&data->mutex);
	data->watermark = val;
	mutex_unlock(&data->mutex);

	return 0;
}