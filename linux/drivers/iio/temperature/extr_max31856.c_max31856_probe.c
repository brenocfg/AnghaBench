#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct spi_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct max31856_data {int thermocouple_type; struct spi_device* spi; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
#define  THERMOCOUPLE_TYPE_B 135 
#define  THERMOCOUPLE_TYPE_E 134 
#define  THERMOCOUPLE_TYPE_J 133 
#define  THERMOCOUPLE_TYPE_K 132 
#define  THERMOCOUPLE_TYPE_N 131 
#define  THERMOCOUPLE_TYPE_R 130 
#define  THERMOCOUPLE_TYPE_S 129 
#define  THERMOCOUPLE_TYPE_T 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_1__*,int) ; 
 int devm_iio_device_register (TYPE_1__*,struct iio_dev*) ; 
 struct max31856_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max31856_channels ; 
 int /*<<< orphan*/  max31856_info ; 
 int max31856_init (struct max31856_data*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int max31856_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct iio_dev *indio_dev;
	struct max31856_data *data;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->spi = spi;

	spi_set_drvdata(spi, indio_dev);

	indio_dev->info = &max31856_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = max31856_channels;
	indio_dev->num_channels = ARRAY_SIZE(max31856_channels);

	ret = of_property_read_u32(spi->dev.of_node, "thermocouple-type",
				   &data->thermocouple_type);

	if (ret) {
		dev_info(&spi->dev,
			 "Could not read thermocouple type DT property, configuring as a K-Type\n");
		data->thermocouple_type = THERMOCOUPLE_TYPE_K;
	}

	/*
	 * no need to translate values as the supported types
	 * have the same value as the #defines
	 */
	switch (data->thermocouple_type) {
	case THERMOCOUPLE_TYPE_B:
	case THERMOCOUPLE_TYPE_E:
	case THERMOCOUPLE_TYPE_J:
	case THERMOCOUPLE_TYPE_K:
	case THERMOCOUPLE_TYPE_N:
	case THERMOCOUPLE_TYPE_R:
	case THERMOCOUPLE_TYPE_S:
	case THERMOCOUPLE_TYPE_T:
		break;
	default:
		dev_err(&spi->dev,
			"error: thermocouple-type %u not supported by max31856\n"
			, data->thermocouple_type);
		return -EINVAL;
	}

	ret = max31856_init(data);
	if (ret) {
		dev_err(&spi->dev, "error: Failed to configure max31856\n");
		return ret;
	}

	return devm_iio_device_register(&spi->dev, indio_dev);
}