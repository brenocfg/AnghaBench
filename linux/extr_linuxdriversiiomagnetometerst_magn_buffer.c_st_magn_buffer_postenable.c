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
struct st_sensor_data {int /*<<< orphan*/ * buffer_data; } ;
struct iio_dev {int /*<<< orphan*/  scan_bytes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_sensors_set_enable (struct iio_dev*,int) ; 

__attribute__((used)) static int st_magn_buffer_postenable(struct iio_dev *indio_dev)
{
	int err;
	struct st_sensor_data *mdata = iio_priv(indio_dev);

	mdata->buffer_data = kmalloc(indio_dev->scan_bytes, GFP_KERNEL);
	if (mdata->buffer_data == NULL) {
		err = -ENOMEM;
		goto allocate_memory_error;
	}

	err = iio_triggered_buffer_postenable(indio_dev);
	if (err < 0)
		goto st_magn_buffer_postenable_error;

	return st_sensors_set_enable(indio_dev, true);

st_magn_buffer_postenable_error:
	kfree(mdata->buffer_data);
allocate_memory_error:
	return err;
}