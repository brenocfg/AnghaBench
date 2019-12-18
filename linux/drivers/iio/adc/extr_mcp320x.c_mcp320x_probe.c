#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {int mode; TYPE_4__ dev; } ;
struct mcp320x_chip_info {int num_channels; int /*<<< orphan*/  resolution; int /*<<< orphan*/  channels; } ;
struct TYPE_8__ {int len; int delay_usecs; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct mcp320x {int /*<<< orphan*/  reg; int /*<<< orphan*/  lock; TYPE_2__ start_conv_transfer; int /*<<< orphan*/  start_conv_msg; TYPE_2__* transfer; int /*<<< orphan*/  msg; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; struct mcp320x_chip_info const* chip_info; struct spi_device* spi; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_9__ {int driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SPI_CPOL ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_4__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mcp320x* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mcp320x_adc_conversion (struct mcp320x*,int /*<<< orphan*/ ,int,int,int*) ; 
 struct mcp320x_chip_info* mcp320x_chip_infos ; 
 int /*<<< orphan*/  mcp320x_info ; 
#define  mcp3550_50 131 
#define  mcp3550_60 130 
#define  mcp3551 129 
#define  mcp3553 128 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int mcp320x_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct mcp320x *adc;
	const struct mcp320x_chip_info *chip_info;
	int ret, device_index;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &mcp320x_info;
	spi_set_drvdata(spi, indio_dev);

	device_index = spi_get_device_id(spi)->driver_data;
	chip_info = &mcp320x_chip_infos[device_index];
	indio_dev->channels = chip_info->channels;
	indio_dev->num_channels = chip_info->num_channels;

	adc->chip_info = chip_info;

	adc->transfer[0].tx_buf = &adc->tx_buf;
	adc->transfer[0].len = sizeof(adc->tx_buf);
	adc->transfer[1].rx_buf = adc->rx_buf;
	adc->transfer[1].len = DIV_ROUND_UP(chip_info->resolution, 8);

	if (chip_info->num_channels == 1)
		/* single-channel converters are rx only (no MOSI pin) */
		spi_message_init_with_transfers(&adc->msg,
						&adc->transfer[1], 1);
	else
		spi_message_init_with_transfers(&adc->msg, adc->transfer,
						ARRAY_SIZE(adc->transfer));

	switch (device_index) {
	case mcp3550_50:
	case mcp3550_60:
	case mcp3551:
	case mcp3553:
		/* rx len increases from 24 to 25 bit in SPI mode 0,0 */
		if (!(spi->mode & SPI_CPOL))
			adc->transfer[1].len++;

		/* conversions are started by asserting CS pin for 8 usec */
		adc->start_conv_transfer.delay_usecs = 8;
		spi_message_init_with_transfers(&adc->start_conv_msg,
						&adc->start_conv_transfer, 1);

		/*
		 * If CS was previously kept low (continuous conversion mode)
		 * and then changed to high, the chip is in shutdown.
		 * Sometimes it fails to wake from shutdown and clocks out
		 * only 0xffffff.  The magic sequence of performing two
		 * conversions without delay between them resets the chip
		 * and ensures all subsequent conversions succeed.
		 */
		mcp320x_adc_conversion(adc, 0, 1, device_index, &ret);
		mcp320x_adc_conversion(adc, 0, 1, device_index, &ret);
	}

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(adc->reg))
		return PTR_ERR(adc->reg);

	ret = regulator_enable(adc->reg);
	if (ret < 0)
		return ret;

	mutex_init(&adc->lock);

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto reg_disable;

	return 0;

reg_disable:
	regulator_disable(adc->reg);

	return ret;
}