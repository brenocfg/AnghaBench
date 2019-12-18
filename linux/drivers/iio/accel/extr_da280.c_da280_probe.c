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
struct iio_dev {char* name; int num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct da280_data {struct i2c_client* client; } ;
typedef  enum da280_chipset { ____Placeholder_da280_chipset } da280_chipset ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int DA280_CHIP_ID ; 
 int /*<<< orphan*/  DA280_REG_CHIP_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int da226 ; 
 int /*<<< orphan*/  da280_channels ; 
 int da280_enable (struct i2c_client*,int) ; 
 int /*<<< orphan*/  da280_info ; 
 int da280_match_acpi_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct da280_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int da280_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct iio_dev *indio_dev;
	struct da280_data *data;
	enum da280_chipset chip;

	ret = i2c_smbus_read_byte_data(client, DA280_REG_CHIP_ID);
	if (ret != DA280_CHIP_ID)
		return (ret < 0) ? ret : -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &da280_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = da280_channels;

	if (ACPI_HANDLE(&client->dev)) {
		chip = da280_match_acpi_device(&client->dev);
	} else {
		chip = id->driver_data;
	}

	if (chip == da226) {
		indio_dev->name = "da226";
		indio_dev->num_channels = 2;
	} else {
		indio_dev->name = "da280";
		indio_dev->num_channels = 3;
	}

	ret = da280_enable(client, true);
	if (ret < 0)
		return ret;

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "device_register failed\n");
		da280_enable(client, false);
	}

	return ret;
}