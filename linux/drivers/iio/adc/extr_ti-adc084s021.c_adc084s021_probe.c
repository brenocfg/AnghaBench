#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_4__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_10__ {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct adc084s021 {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; TYPE_2__ spi_trans; int /*<<< orphan*/  message; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; struct spi_device* spi; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc084s021_buffer_setup_ops ; 
 int /*<<< orphan*/  adc084s021_buffer_trigger_handler ; 
 int /*<<< orphan*/  adc084s021_channels ; 
 int /*<<< orphan*/  adc084s021_info ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_4__*,int) ; 
 int devm_iio_device_register (TYPE_4__*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (TYPE_4__*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_4__*,char*) ; 
 struct adc084s021* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_init_with_transfers (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int adc084s021_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct adc084s021 *adc;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*adc));
	if (!indio_dev) {
		dev_err(&spi->dev, "Failed to allocate IIO device\n");
		return -ENOMEM;
	}

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	/* Connect the SPI device and the iio dev */
	spi_set_drvdata(spi, indio_dev);

	/* Initiate the Industrial I/O device */
	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &adc084s021_info;
	indio_dev->channels = adc084s021_channels;
	indio_dev->num_channels = ARRAY_SIZE(adc084s021_channels);

	/* Create SPI transfer for channel reads */
	adc->spi_trans.tx_buf = adc->tx_buf;
	adc->spi_trans.rx_buf = adc->rx_buf;
	adc->spi_trans.len = 4; /* Trash + single channel */
	spi_message_init_with_transfers(&adc->message, &adc->spi_trans, 1);

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(adc->reg))
		return PTR_ERR(adc->reg);

	mutex_init(&adc->lock);

	/* Setup triggered buffer with pollfunction */
	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, NULL,
					    adc084s021_buffer_trigger_handler,
					    &adc084s021_buffer_setup_ops);
	if (ret) {
		dev_err(&spi->dev, "Failed to setup triggered buffer\n");
		return ret;
	}

	return devm_iio_device_register(&spi->dev, indio_dev);
}