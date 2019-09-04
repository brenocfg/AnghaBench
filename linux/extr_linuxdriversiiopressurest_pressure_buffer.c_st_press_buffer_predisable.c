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
struct st_sensor_data {int /*<<< orphan*/  buffer_data; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int st_sensors_set_enable (struct iio_dev*,int) ; 

__attribute__((used)) static int st_press_buffer_predisable(struct iio_dev *indio_dev)
{
	int err;
	struct st_sensor_data *press_data = iio_priv(indio_dev);

	err = iio_triggered_buffer_predisable(indio_dev);
	if (err < 0)
		goto st_press_buffer_predisable_error;

	err = st_sensors_set_enable(indio_dev, false);

st_press_buffer_predisable_error:
	kfree(press_data->buffer_data);
	return err;
}