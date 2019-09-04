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
typedef  int /*<<< orphan*/  u8 ;
struct st_sensor_data {int /*<<< orphan*/ * buffer_data; } ;
struct iio_dev {scalar_t__* active_scan_mask; int /*<<< orphan*/  scan_bytes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_sensors_set_axis_enable (struct iio_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_accel_buffer_postenable(struct iio_dev *indio_dev)
{
	int err;
	struct st_sensor_data *adata = iio_priv(indio_dev);

	adata->buffer_data = kmalloc(indio_dev->scan_bytes, GFP_KERNEL);
	if (adata->buffer_data == NULL) {
		err = -ENOMEM;
		goto allocate_memory_error;
	}

	err = st_sensors_set_axis_enable(indio_dev,
					(u8)indio_dev->active_scan_mask[0]);
	if (err < 0)
		goto st_accel_buffer_postenable_error;

	err = iio_triggered_buffer_postenable(indio_dev);
	if (err < 0)
		goto st_accel_buffer_postenable_error;

	return err;

st_accel_buffer_postenable_error:
	kfree(adata->buffer_data);
allocate_memory_error:
	return err;
}