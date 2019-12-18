#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; TYPE_6__* channels; int /*<<< orphan*/  modes; TYPE_1__ dev; } ;
struct TYPE_13__ {int len; int /*<<< orphan*/ * rx_buf; } ;
struct ad7766 {int /*<<< orphan*/  msg; TYPE_3__ xfer; int /*<<< orphan*/ * data; struct spi_device* spi; TYPE_4__* trig; int /*<<< orphan*/  pd_gpio; TYPE_6__* reg; int /*<<< orphan*/  mclk; int /*<<< orphan*/ * chip_info; } ;
struct TYPE_15__ {char* supply; } ;
struct TYPE_12__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_14__ {TYPE_2__ dev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 size_t AD7766_SUPPLY_AVDD ; 
 size_t AD7766_SUPPLY_DVDD ; 
 size_t AD7766_SUPPLY_VREF ; 
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_6__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7766_buffer_setup_ops ; 
 TYPE_6__* ad7766_channels ; 
 int /*<<< orphan*/ * ad7766_chip_info ; 
 int /*<<< orphan*/  ad7766_info ; 
 int /*<<< orphan*/  ad7766_irq ; 
 int /*<<< orphan*/  ad7766_trigger_handler ; 
 int /*<<< orphan*/  ad7766_trigger_ops ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 TYPE_4__* devm_iio_trigger_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_iio_trigger_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct ad7766* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_4__*,struct ad7766*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7766_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct iio_dev *indio_dev;
	struct ad7766 *ad7766;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*ad7766));
	if (!indio_dev)
		return -ENOMEM;

	ad7766 = iio_priv(indio_dev);
	ad7766->chip_info = &ad7766_chip_info[id->driver_data];

	ad7766->mclk = devm_clk_get(&spi->dev, "mclk");
	if (IS_ERR(ad7766->mclk))
		return PTR_ERR(ad7766->mclk);

	ad7766->reg[AD7766_SUPPLY_AVDD].supply = "avdd";
	ad7766->reg[AD7766_SUPPLY_DVDD].supply = "dvdd";
	ad7766->reg[AD7766_SUPPLY_VREF].supply = "vref";

	ret = devm_regulator_bulk_get(&spi->dev, ARRAY_SIZE(ad7766->reg),
		ad7766->reg);
	if (ret)
		return ret;

	ad7766->pd_gpio = devm_gpiod_get_optional(&spi->dev, "powerdown",
		GPIOD_OUT_HIGH);
	if (IS_ERR(ad7766->pd_gpio))
		return PTR_ERR(ad7766->pd_gpio);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ad7766_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7766_channels);
	indio_dev->info = &ad7766_info;

	if (spi->irq > 0) {
		ad7766->trig = devm_iio_trigger_alloc(&spi->dev, "%s-dev%d",
			indio_dev->name, indio_dev->id);
		if (!ad7766->trig)
			return -ENOMEM;

		ad7766->trig->ops = &ad7766_trigger_ops;
		ad7766->trig->dev.parent = &spi->dev;
		iio_trigger_set_drvdata(ad7766->trig, ad7766);

		ret = devm_request_irq(&spi->dev, spi->irq, ad7766_irq,
			IRQF_TRIGGER_FALLING, dev_name(&spi->dev),
			ad7766->trig);
		if (ret < 0)
			return ret;

		/*
		 * The device generates interrupts as long as it is powered up.
		 * Some platforms might not allow the option to power it down so
		 * disable the interrupt to avoid extra load on the system
		 */
		disable_irq(spi->irq);

		ret = devm_iio_trigger_register(&spi->dev, ad7766->trig);
		if (ret)
			return ret;
	}

	spi_set_drvdata(spi, indio_dev);

	ad7766->spi = spi;

	/* First byte always 0 */
	ad7766->xfer.rx_buf = &ad7766->data[1];
	ad7766->xfer.len = 3;

	spi_message_init(&ad7766->msg);
	spi_message_add_tail(&ad7766->xfer, &ad7766->msg);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
		&iio_pollfunc_store_time, &ad7766_trigger_handler,
		&ad7766_buffer_setup_ops);
	if (ret)
		return ret;

	ret = devm_iio_device_register(&spi->dev, indio_dev);
	if (ret)
		return ret;
	return 0;
}