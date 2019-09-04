#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ti_ads7950_state {int settings; int /*<<< orphan*/  reg; int /*<<< orphan*/  vref_mv; TYPE_2__* scan_single_xfer; int /*<<< orphan*/  scan_single_msg; int /*<<< orphan*/  single_rx; int /*<<< orphan*/  single_tx; struct spi_device* spi; } ;
struct ti_ads7950_chip_info {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {size_t driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TI_ADS7950_CR_MANUAL ; 
 int TI_ADS7950_CR_RANGE_5V ; 
 int /*<<< orphan*/  TI_ADS7950_VA_MV_ACPI_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ti_ads7950_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 struct ti_ads7950_chip_info* ti_ads7950_chip_info ; 
 int /*<<< orphan*/  ti_ads7950_info ; 
 int /*<<< orphan*/  ti_ads7950_trigger_handler ; 

__attribute__((used)) static int ti_ads7950_probe(struct spi_device *spi)
{
	struct ti_ads7950_state *st;
	struct iio_dev *indio_dev;
	const struct ti_ads7950_chip_info *info;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;
	st->settings = TI_ADS7950_CR_MANUAL | TI_ADS7950_CR_RANGE_5V;

	info = &ti_ads7950_chip_info[spi_get_device_id(spi)->driver_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = info->channels;
	indio_dev->num_channels = info->num_channels;
	indio_dev->info = &ti_ads7950_info;

	/*
	 * Setup default message. The sample is read at the end of the first
	 * transfer, then it takes one full cycle to convert the sample and one
	 * more cycle to send the value. The conversion process is driven by
	 * the SPI clock, which is why we have 3 transfers. The middle one is
	 * just dummy data sent while the chip is converting the sample that
	 * was read at the end of the first transfer.
	 */

	st->scan_single_xfer[0].tx_buf = &st->single_tx;
	st->scan_single_xfer[0].len = 2;
	st->scan_single_xfer[0].cs_change = 1;
	st->scan_single_xfer[1].tx_buf = &st->single_tx;
	st->scan_single_xfer[1].len = 2;
	st->scan_single_xfer[1].cs_change = 1;
	st->scan_single_xfer[2].rx_buf = &st->single_rx;
	st->scan_single_xfer[2].len = 2;

	spi_message_init_with_transfers(&st->scan_single_msg,
					st->scan_single_xfer, 3);

	/* Use hard coded value for reference voltage in ACPI case */
	if (ACPI_COMPANION(&spi->dev))
		st->vref_mv = TI_ADS7950_VA_MV_ACPI_DEFAULT;

	st->reg = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(st->reg)) {
		dev_err(&spi->dev, "Failed get get regulator \"vref\"\n");
		return PTR_ERR(st->reg);
	}

	ret = regulator_enable(st->reg);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable regulator \"vref\"\n");
		return ret;
	}

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 &ti_ads7950_trigger_handler, NULL);
	if (ret) {
		dev_err(&spi->dev, "Failed to setup triggered buffer\n");
		goto error_disable_reg;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&spi->dev, "Failed to register iio device\n");
		goto error_cleanup_ring;
	}

	return 0;

error_cleanup_ring:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);

	return ret;
}