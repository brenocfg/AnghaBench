#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max517_platform_data {int* vref_mv; } ;
struct max517_data {int* vref_mv; struct i2c_client* client; } ;
struct TYPE_3__ {TYPE_2__* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_4__ {struct max517_platform_data* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
#define  ID_MAX518 131 
#define  ID_MAX519 130 
#define  ID_MAX520 129 
#define  ID_MAX521 128 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct max517_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max517_channels ; 
 int /*<<< orphan*/  max517_info ; 

__attribute__((used)) static int max517_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct max517_data *data;
	struct iio_dev *indio_dev;
	struct max517_platform_data *platform_data = client->dev.platform_data;
	int chan;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	/* establish that the iio_dev is a child of the i2c device */
	indio_dev->dev.parent = &client->dev;

	switch (id->driver_data) {
	case ID_MAX521:
		indio_dev->num_channels = 8;
		break;
	case ID_MAX520:
		indio_dev->num_channels = 4;
		break;
	case ID_MAX519:
	case ID_MAX518:
		indio_dev->num_channels = 2;
		break;
	default:  /* single channel for MAX517 */
		indio_dev->num_channels = 1;
		break;
	}
	indio_dev->channels = max517_channels;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &max517_info;

	/*
	 * Reference voltage on MAX518 and default is 5V, else take vref_mv
	 * from platform_data
	 */
	for (chan = 0; chan < indio_dev->num_channels; chan++) {
		if (id->driver_data == ID_MAX518 || !platform_data)
			data->vref_mv[chan] = 5000; /* mV */
		else
			data->vref_mv[chan] = platform_data->vref_mv[chan];
	}

	return iio_device_register(indio_dev);
}