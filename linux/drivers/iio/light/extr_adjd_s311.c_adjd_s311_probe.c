#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adjd_s311_data {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJD_S311_DRV_NAME ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  adjd_s311_channels ; 
 int /*<<< orphan*/  adjd_s311_info ; 
 int /*<<< orphan*/  adjd_s311_trigger_handler ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct adjd_s311_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adjd_s311_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct adjd_s311_data *data;
	struct iio_dev *indio_dev;
	int err;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (indio_dev == NULL)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &adjd_s311_info;
	indio_dev->name = ADJD_S311_DRV_NAME;
	indio_dev->channels = adjd_s311_channels;
	indio_dev->num_channels = ARRAY_SIZE(adjd_s311_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	err = iio_triggered_buffer_setup(indio_dev, NULL,
		adjd_s311_trigger_handler, NULL);
	if (err < 0)
		return err;

	err = iio_device_register(indio_dev);
	if (err)
		goto exit_unreg_buffer;

	dev_info(&client->dev, "ADJD-S311 color sensor registered\n");

	return 0;

exit_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
	return err;
}