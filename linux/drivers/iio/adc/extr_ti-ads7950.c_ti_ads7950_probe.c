#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int base; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  owner; int /*<<< orphan*/ * parent; int /*<<< orphan*/  label; } ;
struct TYPE_8__ {int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct ti_ads7950_state {int /*<<< orphan*/  slock; int /*<<< orphan*/  reg; TYPE_5__ chip; struct spi_device* spi; int /*<<< orphan*/  vref_mv; TYPE_2__* scan_single_xfer; int /*<<< orphan*/  scan_single_msg; int /*<<< orphan*/  single_rx; int /*<<< orphan*/  single_tx; int /*<<< orphan*/  ring_msg; TYPE_3__ ring_xfer; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct ti_ads7950_chip_info {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {size_t driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CS_WORD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  TI_ADS7950_NUM_GPIOS ; 
 int /*<<< orphan*/  TI_ADS7950_VA_MV_ACPI_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int gpiochip_add_data (TYPE_5__*,struct ti_ads7950_state*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ti_ads7950_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_4__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int spi_setup (struct spi_device*) ; 
 struct ti_ads7950_chip_info* ti_ads7950_chip_info ; 
 int /*<<< orphan*/  ti_ads7950_direction_input ; 
 int /*<<< orphan*/  ti_ads7950_direction_output ; 
 int /*<<< orphan*/  ti_ads7950_get ; 
 int /*<<< orphan*/  ti_ads7950_get_direction ; 
 int /*<<< orphan*/  ti_ads7950_info ; 
 int ti_ads7950_init_hw (struct ti_ads7950_state*) ; 
 int /*<<< orphan*/  ti_ads7950_set ; 
 int /*<<< orphan*/  ti_ads7950_trigger_handler ; 

__attribute__((used)) static int ti_ads7950_probe(struct spi_device *spi)
{
	struct ti_ads7950_state *st;
	struct iio_dev *indio_dev;
	const struct ti_ads7950_chip_info *info;
	int ret;

	spi->bits_per_word = 16;
	spi->mode |= SPI_CS_WORD;
	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "Error in spi setup\n");
		return ret;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	info = &ti_ads7950_chip_info[spi_get_device_id(spi)->driver_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = info->channels;
	indio_dev->num_channels = info->num_channels;
	indio_dev->info = &ti_ads7950_info;

	/* build spi ring message */
	spi_message_init(&st->ring_msg);

	st->ring_xfer.tx_buf = &st->tx_buf[0];
	st->ring_xfer.rx_buf = &st->rx_buf[0];
	/* len will be set later */
	st->ring_xfer.cs_change = true;

	spi_message_add_tail(&st->ring_xfer, &st->ring_msg);

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

	mutex_init(&st->slock);

	st->reg = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(st->reg)) {
		dev_err(&spi->dev, "Failed get get regulator \"vref\"\n");
		ret = PTR_ERR(st->reg);
		goto error_destroy_mutex;
	}

	ret = regulator_enable(st->reg);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable regulator \"vref\"\n");
		goto error_destroy_mutex;
	}

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 &ti_ads7950_trigger_handler, NULL);
	if (ret) {
		dev_err(&spi->dev, "Failed to setup triggered buffer\n");
		goto error_disable_reg;
	}

	ret = ti_ads7950_init_hw(st);
	if (ret) {
		dev_err(&spi->dev, "Failed to init adc chip\n");
		goto error_cleanup_ring;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&spi->dev, "Failed to register iio device\n");
		goto error_cleanup_ring;
	}

	/* Add GPIO chip */
	st->chip.label = dev_name(&st->spi->dev);
	st->chip.parent = &st->spi->dev;
	st->chip.owner = THIS_MODULE;
	st->chip.base = -1;
	st->chip.ngpio = TI_ADS7950_NUM_GPIOS;
	st->chip.get_direction = ti_ads7950_get_direction;
	st->chip.direction_input = ti_ads7950_direction_input;
	st->chip.direction_output = ti_ads7950_direction_output;
	st->chip.get = ti_ads7950_get;
	st->chip.set = ti_ads7950_set;

	ret = gpiochip_add_data(&st->chip, st);
	if (ret) {
		dev_err(&spi->dev, "Failed to init GPIOs\n");
		goto error_iio_device;
	}

	return 0;

error_iio_device:
	iio_device_unregister(indio_dev);
error_cleanup_ring:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);
error_destroy_mutex:
	mutex_destroy(&st->slock);

	return ret;
}