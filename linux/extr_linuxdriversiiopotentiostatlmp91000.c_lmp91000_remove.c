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
struct lmp91000_data {int /*<<< orphan*/  trig; int /*<<< orphan*/  cb_buffer; } ;
struct iio_dev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct iio_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  iio_channel_release_all_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_channel_stop_all_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct lmp91000_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 

__attribute__((used)) static int lmp91000_remove(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct lmp91000_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	iio_channel_stop_all_cb(data->cb_buffer);
	iio_channel_release_all_cb(data->cb_buffer);

	iio_triggered_buffer_cleanup(indio_dev);
	iio_trigger_unregister(data->trig);

	return 0;
}