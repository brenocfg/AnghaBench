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
struct spi_device {int /*<<< orphan*/  dev; scalar_t__ irq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad7816_chip_info {int* oti_data; scalar_t__ id; void* busy_pin; void* convert_pin; void* rdwr_pin; struct spi_device* spi_dev; } ;
struct TYPE_4__ {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AD7816_CS_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ ID_AD7816 ; 
 scalar_t__ ID_AD7817 ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ad7816_event_handler ; 
 int /*<<< orphan*/  ad7816_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct iio_dev*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int ad7816_probe(struct spi_device *spi_dev)
{
	struct ad7816_chip_info *chip;
	struct iio_dev *indio_dev;
	int i, ret;

	indio_dev = devm_iio_device_alloc(&spi_dev->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);
	/* this is only used for device removal purposes */
	dev_set_drvdata(&spi_dev->dev, indio_dev);

	chip->spi_dev = spi_dev;
	for (i = 0; i <= AD7816_CS_MAX; i++)
		chip->oti_data[i] = 203;

	chip->id = spi_get_device_id(spi_dev)->driver_data;
	chip->rdwr_pin = devm_gpiod_get(&spi_dev->dev, "rdwr", GPIOD_OUT_HIGH);
	if (IS_ERR(chip->rdwr_pin)) {
		ret = PTR_ERR(chip->rdwr_pin);
		dev_err(&spi_dev->dev, "Failed to request rdwr GPIO: %d\n",
			ret);
		return ret;
	}
	chip->convert_pin = devm_gpiod_get(&spi_dev->dev, "convert",
					   GPIOD_OUT_HIGH);
	if (IS_ERR(chip->convert_pin)) {
		ret = PTR_ERR(chip->convert_pin);
		dev_err(&spi_dev->dev, "Failed to request convert GPIO: %d\n",
			ret);
		return ret;
	}
	if (chip->id == ID_AD7816 || chip->id == ID_AD7817) {
		chip->busy_pin = devm_gpiod_get(&spi_dev->dev, "busy",
						GPIOD_IN);
		if (IS_ERR(chip->busy_pin)) {
			ret = PTR_ERR(chip->busy_pin);
			dev_err(&spi_dev->dev, "Failed to request busy GPIO: %d\n",
				ret);
			return ret;
		}
	}

	indio_dev->name = spi_get_device_id(spi_dev)->name;
	indio_dev->dev.parent = &spi_dev->dev;
	indio_dev->info = &ad7816_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (spi_dev->irq) {
		/* Only low trigger is supported in ad7816/7/8 */
		ret = devm_request_threaded_irq(&spi_dev->dev, spi_dev->irq,
						NULL,
						&ad7816_event_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		if (ret)
			return ret;
	}

	ret = devm_iio_device_register(&spi_dev->dev, indio_dev);
	if (ret)
		return ret;

	dev_info(&spi_dev->dev, "%s temperature sensor and ADC registered.\n",
		 indio_dev->name);

	return 0;
}